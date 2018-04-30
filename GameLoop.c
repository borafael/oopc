#include "GameLoop.h"

GameLoop* create_game_loop(HandleInput hi, Update u, Render r) {
	GameLoop* gl = (GameLoop*)malloc(sizeof(GameLoop));
	gl->handle_input = hi;
	gl->update = u;
	gl->render = r;
	return gl;
}

void destroy_game_loop(GameLoop* gl) {
	free(gl);
}
