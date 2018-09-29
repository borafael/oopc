#include "GameLoop.h"

GameLoop* create_game_loop(HandleInput hi, Update u, Render r, ShouldContinue sc) {
	GameLoop* gl = (GameLoop*)malloc(sizeof(GameLoop));
	gl->handle_input = hi;
	gl->update = u;
	gl->render = r;
	gl->should_continue = sc;
	return gl;
}

void start_game_loop(GameLoop* gl, ServiceLocator* sl) {
	while(gl->should_continue(sl)) {
		gl->handle_input(sl);
		gl->update(sl);
		gl->render(sl);
	}
}

void destroy_game_loop(GameLoop* gl) {
	free(gl);
}
