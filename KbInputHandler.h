#ifndef __KBINPUTHANDLER_H__
#define __KBINPUTHANDLER_H__

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/keyboard.h>
#include <linux/kd.h>

typedef struct {
	/* keyboard device file descriptor*/
	int kb_fd;
	/* */
	struct termios old_term;
	/* */
	int old_mode;
	/* Our key-mapping table. This will contain printable characters
	for some keys. */
	char keymap[NR_KEYS];
	/* We’ll assign names to certain keys. */
	char* keynames[NR_KEYS];
} KbInputHandler;

typedef struct {
	char key_code;
	int is_release;
} KbInput;

KbInputHandler* create_kb_input_handler();

void capture_kb(KbInputHandler* kb_input_handler);

KbInput get_kb_input(KbInputHandler* kb_input_handler);

void release_kb(KbInputHandler* kb_input_handler);

void destroy_kb_input_handler(KbInputHandler* kb_input_handler);

#endif
