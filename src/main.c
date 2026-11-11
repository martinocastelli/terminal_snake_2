#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "renderer.h"
#include "tc.h"


typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} direction_e;

typedef struct {
	size_t x;
	size_t y;
} coord_t;

typedef struct {
	coord_t *arr;
	uint16_t size;
	size_t max_size;
} body_t; 

typedef struct {
	cell_type_e board[BOARD_SIZE_X][BOARD_SIZE_Y];
	direction_e dir;
	direction_e old_dir;
	body_t body; 
	coord_t apple_pos;
} snake_t;

static snake_t snake;

static void increase_snake_size();
static void init_data();
static void read_input();
static void move_snake();
static void end_game();
static void spawn_new_apple();


int main() {
	srand(time(NULL));
	init_renderer();

	init_data();

	while(true) {
		read_input();
		move_snake();
		render_board(snake.board);
		usleep(200000);
	}

	end_renderer();

	return 0;
}
static void increase_snake_size() {
	if(snake.body.size >= snake.body.max_size) {
		snake.body.arr = (coord_t*)realloc(snake.body.arr, (snake.body.max_size + 1) * sizeof(coord_t));
		assert(snake.body.arr != NULL);
		snake.body.max_size++;
	}
	snake.body.size++;
}
static void init_data() {
	memset(&snake, 0, sizeof(snake));
	for(size_t x = 0;x < BOARD_SIZE_X;x++) {
		for(size_t y = 0;y < BOARD_SIZE_Y;y++) {
			snake.board[x][y] = NOTHING;
		}
	}

	snake.board[0][0] = SNAKE;
	snake.old_dir = DOWN;
	snake.dir = DOWN;

	snake.body.arr = (coord_t*)malloc(INITIAL_SNAKE_SIZE * sizeof(coord_t));
	snake.body.size = INITIAL_SNAKE_SIZE;
	snake.body.max_size = INITIAL_SNAKE_SIZE;
	snake.body.arr[0] = (coord_t){0, 1};
	snake.body.arr[1] = (coord_t){0, 0};

	snake.board[0][4] = APPLE;
}
void read_input() {
	tc_keyboard_input_d input = tc_get_pressed_keys();
	for(size_t i = 0; i < input.normal_input_size;i++) {
		switch(input.normal_input[i]) {
			case 'w':
			case 'k':
				snake.dir = UP;
				break;
			case 's':
			case 'j':
				snake.dir = DOWN;
				break;
			case 'd':
			case 'l':
				snake.dir = RIGHT;
				break;
			case 'a':
			case 'h':
				snake.dir = LEFT;
				break;
			default:
		}
	}
	for(size_t i = 0; i < input.escape_input_size;i++) {
		switch(input.escape_input[i]) {
			case TC_ARROW_UP:
				snake.dir = UP;
				break;
			case TC_ARROW_DOWN:
				snake.dir = DOWN;
				break;
			case TC_ARROW_RIGHT:
				snake.dir = RIGHT;
				break;
			case TC_ARROW_LEFT:
				snake.dir = LEFT;
				break;
			default:
		}
	}
	switch(snake.old_dir) {
		case UP:
			if(snake.dir != DOWN) {
				snake.old_dir = snake.dir;
			} else {
				snake.dir = UP;
			}
			break;
		case DOWN:
			if(snake.dir != UP) {
				snake.old_dir = snake.dir;
			} else {
				snake.dir = DOWN;
			}
			break;
		case RIGHT:
			if(snake.dir != LEFT) {
				snake.old_dir = snake.dir;
			} else {
				snake.dir = RIGHT;
			}
			break;
		case LEFT:
			if(snake.dir != RIGHT) {
				snake.old_dir = snake.dir;
			} else {
				snake.dir = LEFT;
			}
			break;
		default:
	}
}
void move_snake() {
	coord_t target;
	target = snake.body.arr[0];
	switch(snake.dir) {
		case UP:
			if(target.y-- <= 0) {
				end_game();
			}
			break;
		case DOWN:
			if(++target.y >= BOARD_SIZE_Y) {
				end_game();
			}
			break;
		case RIGHT:
			if(++target.x >= BOARD_SIZE_X) {
				end_game();
			}
			break;
		case LEFT:
			if(target.x-- <= 0) {
				end_game();
			}
			break;
		default:
	}
	snake.board[snake.body.arr[snake.body.size - 1].x][snake.body.arr[snake.body.size - 1].y] = NOTHING;
	if(snake.board[target.x][target.y] == APPLE) {
		increase_snake_size();
		spawn_new_apple();
	}
	for(size_t i = snake.body.size - 1; i > 0;i--) {
		snake.body.arr[i] = snake.body.arr[i - 1];
	}
	snake.board[snake.body.arr[0].x][snake.body.arr[0].y] = SNAKE;
	snake.body.arr[0] = target;
	snake.board[snake.body.arr[0].x][snake.body.arr[0].y] = SNAKE_HEAD;
}
void end_game() {
	end_renderer();
	exit(0);
}
static void spawn_new_apple() {
	coord_t target;
	for(size_t i = 0;i < 1024;i++) {
		target.x = rand() % BOARD_SIZE_X;
		target.y = rand() % BOARD_SIZE_Y;
		if(snake.board[target.x][target.y] == NOTHING) {
			snake.board[target.x][target.y] = APPLE;
			return;
		}
	}
	fprintf(stderr, "no place for apple found, aborting\n");
	end_game();
}
