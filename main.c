#include <stdio.h>
#include "GameLoop.h"
#include "KbInputHandler.h"

#define KB_INPUT 0

void handle_input(ServiceLocator* sl) {}

void update(ServiceLocator* sl) {}

void render(ServiceLocator* sl) {}

int should_continue(ServiceLocator* sl) {
	KbInputHandler* kb_input_handler = get_service(sl, KB_INPUT);
	KbInput kb_input = get_kb_input(kb_input_handler);
	printf("%d %s %s\n", kb_input.key_code, kb_input.key_name, kb_input.is_release ? "released" : "pressed");
	return kb_input.key_code != 1;
}

int main(int argc, char** argv) {
	KbInputHandler* kb_input_handler = create_kb_input_handler();
	capture_kb(kb_input_handler);
	ServiceLocator* sl = create_service_locator(10);
	store_service(sl, KB_INPUT, kb_input_handler);
	GameLoop* gl = create_game_loop(&handle_input, &update, &render, &should_continue);

	start_game_loop(gl, sl);
	destroy_game_loop(gl);
	release_kb(kb_input_handler);
	destroy_kb_input_handler(kb_input_handler);
	destroy_service_locator(sl);
	return 0;
}
