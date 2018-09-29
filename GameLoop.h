#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include "ServiceLocator.h"
#include <stdlib.h>

typedef void (*HandleInput)(ServiceLocator* sl);

typedef void (*Update)(ServiceLocator * sl);

typedef void (*Render)(ServiceLocator * sl);

typedef int (*ShouldContinue)(ServiceLocator * sl);

typedef struct {
	HandleInput handle_input;
	Update update;
	Render render;
	ShouldContinue should_continue;
} GameLoop;

GameLoop* create_game_loop(HandleInput hi, Update u, Render r, ShouldContinue sc);

void start_game_loop(GameLoop* gl, ServiceLocator* sl);

void destroy_game_loop(GameLoop* gl);

#endif
