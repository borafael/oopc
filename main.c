#include <stdio.h>
#include "GameLoop.h"

void handle_input(ServiceLocator* sl) {}

void update(ServiceLocator* sl) {}

void render(ServiceLocator* sl) {}

int should_continue(ServiceLocator* sl) {
	return 0;
}

int main(int argc, char** argv) {

	ServiceLocator* sl = create_service_locator(10);

	GameLoop* gl = create_game_loop(&handle_input, &update, &render, & should_continue);
	start_game_loop(gl, sl);
	destroy_game_loop(gl);

	destroy_service_locator(sl);
	return 0;
}
