#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <stdint.h>

#include "game_conf.h"

typedef enum {
	NOTHING,
	APPLE,
	SNAKE,
	SNAKE_HEAD,
} cell_type_e;


void init_renderer();
void end_renderer();
void render_board(cell_type_e board[BOARD_SIZE_X][BOARD_SIZE_Y], uint16_t score, uint16_t best_score);

#endif //_RENDERER_H_
