#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "renderer.h"
#include "tc.h"

typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} direction_e;

typedef struct {
	cell_type_e board[BOARD_SIZE_X][BOARD_SIZE_Y];
	uint16_t score;
	direction_e dir;
	direction_e old_dir;
	size_t head_x_pos;
	size_t head_y_pos;
} game_data_t;

static game_data_t game_data;

void read_input();
void move_snake();
void end_game();

int main() {
	init_renderer();

	memset(&game_data, 0, sizeof(game_data));
	for(size_t x = 0;x < BOARD_SIZE_X;x++) {
		for(size_t y = 0;y < BOARD_SIZE_Y;y++) {
			game_data.board[x][y] = NOTHING;
		}
	}

	game_data.board[0][0] = SNAKE_HEAD;
	game_data.head_x_pos = 0;
	game_data.head_y_pos = 0;
	game_data.old_dir = DOWN;
	game_data.dir = DOWN;
	while(true) {
		read_input();
		move_snake();
		render_board(game_data.board);
		usleep(200000);
	}

	end_renderer();

	return 0;
}
void read_input() {
	static tc_keyboard_input_d input = {NULL, 0, NULL, 0};
	tc_get_pressed_keys(&input);
	for(size_t i = 0; i < input.normal_input_size;i++) {
		switch(input.normal_input[i]) {
			case 'w':
			case 'k':
				game_data.dir = UP;
				break;
			case 's':
			case 'j':
				game_data.dir = DOWN;
				break;
			case 'd':
			case 'l':
				game_data.dir = RIGHT;
				break;
			case 'a':
			case 'h':
				game_data.dir = LEFT;
				break;
			default:
		}
	}
	for(size_t i = 0; i < input.escape_input_size;i++) {
		switch(input.escape_input[i]) {
			case TC_ARROW_UP:
				game_data.dir = UP;
				break;
			case TC_ARROW_DOWN:
				game_data.dir = DOWN;
				break;
			case TC_ARROW_RIGHT:
				game_data.dir = RIGHT;
				break;
			case TC_ARROW_LEFT:
				game_data.dir = LEFT;
				break;
			default:
		}
	}
	switch(game_data.old_dir) {
		case UP:
			if(game_data.dir != DOWN) {
				game_data.old_dir = game_data.dir;
			} else {
				game_data.dir = UP;
			}
			break;
		case DOWN:
			if(game_data.dir != UP) {
				game_data.old_dir = game_data.dir;
			} else {
				game_data.dir = DOWN;
			}
			break;
		case RIGHT:
			if(game_data.dir != LEFT) {
				game_data.old_dir = game_data.dir;
			} else {
				game_data.dir = RIGHT;
			}
			break;
		case LEFT:
			if(game_data.dir != RIGHT) {
				game_data.old_dir = game_data.dir;
			} else {
				game_data.dir = LEFT;
			}
			break;
		default:
	}
}
void move_snake() {
	size_t target_x, target_y;
	target_x = game_data.head_x_pos;
	target_y = game_data.head_y_pos;
	switch(game_data.dir) {
		case UP:
			if(target_y-- <= 0) {
				end_game();
			}
			break;
		case DOWN:
			if(++target_y >= BOARD_SIZE_Y) {
				end_game();
			}
			break;
		case RIGHT:
			if(++target_x >= BOARD_SIZE_X) {
				end_game();
			}
			break;
		case LEFT:
			if(target_x-- <= 0) {
				end_game();
			}
			break;
		default:
	}
	game_data.board[game_data.head_x_pos][game_data.head_y_pos] = SNAKE_BODY;
	game_data.board[target_x][target_y] = SNAKE_HEAD;
	game_data.head_x_pos = target_x;
	game_data.head_y_pos = target_y;
}
void end_game() {
	end_renderer();
	exit(0);
}
