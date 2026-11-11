#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "game_conf.h"

typedef enum {
	NOTHING,
	APPLE,
	SNAKE,
	SNAKE_HEAD,
} cell_type_e;


void init_renderer();
void end_renderer();
void render_board(cell_type_e board[BOARD_SIZE_X][BOARD_SIZE_Y]);

#endif //_RENDERER_H_
