#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include "ServiceLocator.h"
#include <stdlib.h>

typedef void (*HandleInput)(ServiceLocator* sl);

typedef void (*Update)(ServiceLocator * sl);

typedef void (*Render)(ServiceLocator * sl);

typedef struct {
	HandleInput handle_input;
	Update update;
	Render render;
} GameLoop;

GameLoop* create_game_loop(HandleInput hi, Update u, Render r);

void destroy_game_loop(GameLoop* gl);

#endif
