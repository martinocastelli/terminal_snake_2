#include "snake.h"

typedef struct {
	uint16_t x;
	uint16_t y;
} coords_d;

enum {
	SNAKE_ARR_INCREMENT_STEP = 16,
};
const coords_d DEFAULT_INITIAL_SNAKE_POS[] = {{0,0},{1,1},{2,2},{3,3},{4,4}};
const size_t DEFAULT_INITIAL_SNAKE_SIZE = sizeof(DEFAULT_INITIAL_SNAKE_POS)/sizeof(DEFAULT_INITIAL_SNAKE_POS[0]);

typedef struct {
	coords_d *pos;
	size_t len;
	size_t max_len;
}snake_form_d;

typedef struct {
	coords_d apple_location;
	snake_form_d snake;
	coords_d board_size;
	bool game_end;
	bool move_snake;
} game_d;
static game_d game;

static void increase_snake_arr(size_t inc);
static void move_snake_once(coords_d target);
static void render_board(bool redraw_all);

bool snake_game(uint16_t *result, uint16_t size_x, uint16_t size_y, uint16_t *initial_pos_x, uint16_t *initial_pos_y, size_t initial_len) {
	if (initial_pos_x == NULL || initial_pos_y == NULL) {
		if(initial_len != 0) {
			return false;
		} else {
			increase_snake_arr(SNAKE_ARR_INCREMENT_STEP);
			for(size_t i = 0;i < DEFAULT_INITIAL_SNAKE_SIZE;i++) {
				game.snake.pos[i] = DEFAULT_INITIAL_SNAKE_POS[i];
			}
		}
	} else {
		while(game.snake.max_len < initial_len) {
			increase_snake_arr(SNAKE_ARR_INCREMENT_STEP);
		}
		for(size_t i = 0;i < initial_len;i++) {
			game.snake.pos[i].x = initial_pos_x[i];
			game.snake.pos[i].y = initial_pos_y[i];
		}
	}
	while(game.game_end == false) {
		if(game.
	}
	

	return true;
}

static void increase_snake_arr(size_t inc) {
	
}
static void move_snake_once(coords_d target) {

}
static void render_board(bool redraw_all) {

}
