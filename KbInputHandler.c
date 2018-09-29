#include "KbInputHandler.h"

/* Locates the arrow keys and the Escape key in the kernel’s keymaps.
Fills in the appropriate globals. */
void init_keymap(KbInputHandler* kb_input_handler) {
	struct kbentry entry;
	int keycode;

	for (keycode = 0; keycode < NR_KEYS; keycode++) {
		kb_input_handler->keymap[keycode] = ' ';
		kb_input_handler->keynames[keycode] = "(unknown)";

		/* Look up this key. If the lookup fails, ignore.
		If it succeeds, KVAL(entry.kb_value) will be the
		8-bit representation of the character the kernel
		has mapped to this keycode. */

		entry.kb_table = 0;
		entry.kb_index = keycode;

		if (ioctl(kb_input_handler->kb_fd, KDGKBENT, &entry) != 0) continue;

		/* Is this a printable character?
		NOTE: we do not handle Unicode translation here.
		See the SDL source (SDL_fbevents.c) for
		an example of how this can be done.
		Add in KT_LATIN and KT_ASCII if you want a wider
		range of characters. They’re omitted here because
		some characters do not print cleanly. */

		if (KTYP(entry.kb_value) == KT_LETTER) {
			kb_input_handler->keymap[keycode] = KVAL(entry.kb_value);
			kb_input_handler->keynames[keycode] = "(letter)";
		}

		/* Since the arrow keys are useful in games, we’ll pick
		them out of the swarm. While we’re at it, we’ll grab
		Enter, Ctrl, and Alt. */

		if (entry.kb_value == K_LEFT)
			kb_input_handler->keynames[keycode] = "Left arrow";
		if (entry.kb_value == K_RIGHT)
			kb_input_handler->keynames[keycode] = "Right arrow";
		if (entry.kb_value == K_DOWN)
			kb_input_handler->keynames[keycode] = "Down arrow";
		if (entry.kb_value == K_UP)
			kb_input_handler->keynames[keycode] = "Up arrow";
		if (entry.kb_value == K_ENTER)
			kb_input_handler->keynames[keycode] = "Enter";
		if (entry.kb_value == K_ALT)
			kb_input_handler->keynames[keycode] = "Left Alt";
		if (entry.kb_value == K_ALTGR)
			kb_input_handler->keynames[keycode] = "Right Alt";
	}

	/* Manually plug in keys that the kernel doesn’t
	normally map correctly. */
	kb_input_handler->keynames[29] = "Left control";
	kb_input_handler->keynames[97] = "Right control";
	kb_input_handler->keynames[125] = "Left Linux key";/* usually mislabelled */
	kb_input_handler->keynames[126] = "Right Linux key";/* with a Windows(tm) logo */
	kb_input_handler->keynames[127] = "Application key";
}

/*
Checks whether or not the given file descriptor is associated with a local
keyboard. Returns 1 if it is, 0 if not (or if something prevented us from
checking).
*/
int is_keyboard(int fd) {

	int data;

	/* See if the keyboard driver groks this file descriptor. */

	data = 0;

	if (ioctl(fd, KDGKBTYPE, &data) != 0)
		return 0;

	/* In current versions of Linux, the keyboard driver always
	answers KB_101 to keyboard type queries. It’s probably
	sufficient to just check whether the above ioctl succeeds
	or fails. */

	if (data == KB_84) {
		printf("84-key keyboard found.\n");
		return 1;
	} else if (data == KB_101) {
		printf("101-key keyboard found.\n");
		return 1;
	}

	/* Sorry, this didn’t check out. */
	return 0;
}

int get_kb_fd() {
	char *files_to_try[] = {"/dev/tty", "/dev/console", NULL};

	int i;

	int fd = -1;

	for (i = 0; files_to_try[i] != NULL; i++) {
		/* Try to open the file. */
		fd = open(files_to_try[i], O_RDONLY);
		if (fd < 0) continue;
		/* See if this is valid for our purposes. */
		if (is_keyboard(fd)) {
			printf("Using keyboard on %s.\n", files_to_try[i]);
			break;
		}

		close(fd);
	}

	return fd;
}

KbInputHandler* create_kb_input_handler() {
	KbInputHandler* kb_input_handler = (KbInputHandler*)malloc(sizeof(KbInputHandler));
	return kb_input_handler;
}

void capture_kb(KbInputHandler* kb_input_handler) {
	struct termios new_term;

	int kb = get_kb_fd();

	/* Find the keyboard’s mode so we can restore it later. */
	if (ioctl(kb, KDGKBMODE, &kb_input_handler->old_mode) != 0) {
		printf("Unable to query keyboard mode.\n");
		exit(1);
	}

	/* Adjust the terminal’s settings. In particular, disable
	echoing, signal generation, and line buffering. Any of
	these could cause trouble. Save the old settings first. */
	if (tcgetattr(kb, &kb_input_handler->old_term) != 0) {
		printf("Unable to query terminal settings.\n");
		exit(1);
	}

	new_term = kb_input_handler->old_term;
	new_term.c_iflag = 0;
	new_term.c_lflag &= ~(ECHO | ICANON | ISIG);

	/* TCSAFLUSH discards unread input before making the change.
	A good idea. */
	if (tcsetattr(kb, TCSAFLUSH, &new_term) != 0) {
		printf("Unable to change terminal settings.\n");
	}
	/* Put the keyboard in mediumraw mode. */
	if (ioctl(kb, KDSKBMODE, K_MEDIUMRAW) != 0) {
		printf("Unable to set mediumraw mode.\n");
		exit(1);
	}

	kb_input_handler->kb_fd = kb;

	init_keymap(kb_input_handler);
}

KbInput get_kb_input(KbInputHandler* kb_input_handler) {
	KbInput kb_input;

	unsigned char data;
	if (read(kb_input_handler->kb_fd, &data, 1) < 1) {
		printf("Unable to read data. Trying to exit nicely.\n");
		exit(1);
	}

	kb_input.key_code = (unsigned int)data & 0x7F;
	kb_input.is_release = (data & 0x80);

	return kb_input;
}

void release_kb(KbInputHandler* kb_input_handler) {
		printf("Exiting normally.\n");
		ioctl(kb_input_handler->kb_fd, KDSKBMODE, kb_input_handler->old_mode);
		tcsetattr(kb_input_handler->kb_fd, 0, &kb_input_handler->old_term);
}

void destroy_kb_input_handler(KbInputHandler* kb_input_handler) {
	free(kb_input_handler);
}
