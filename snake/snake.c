#include <stdio.h>
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
static coords_d get_next_snake_pos(void);
static bool check_next_snake_pos(coords_d target);
static void move_snake_once(coords_d target, bool with_apple);
static void render_board(bool redraw_all);
static void spawn_new_apple(void);

bool snake_game(uint16_t *result, uint16_t size_x, uint16_t size_y, uint16_t *initial_pos_x, uint16_t *initial_pos_y, size_t initial_len) {
	game.snake.max_len = 0;
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
		if(game.move_snake == true) {
			coords_d buff = get_next_snake_pos();
			if(check_next_snake_pos(buff) == true) {
				move_snake_once(buff, buff.x == game.apple_location.x && buff.y == game.apple_location.y);
			} else {
				game.game_end = true;
			}
			render_board(false);
			game.move_snake = false;
		}
	}

	return true;
}

static void increase_snake_arr(size_t inc) {
	coords_d *buff = (coords_d*)malloc((game.snake.max_len + inc) * sizeof(coords_d));
	for(size_t i = 0;i < game.snake.max_len;i++) {
		buff[i] = game.snake.pos[i];
	}
	free(game.snake.pos);
	game.snake.pos = buff;
}
static coords_d get_next_snake_pos(void) {
	coords_d result = game.snake.pos[0];
	result.x++;
	return result;
}
static bool check_next_snake_pos(coords_d target) {
	for(size_t i = 0;i < game.snake.len;i++) {
		if (target.x == game.snake.pos[i].x && target.y == game.snake.pos[i].y) {
			return false;
		}
	}
	if(target.x <= 1 || target.x >= (game.board_size.x + 1) || target.y <= 1 || target.y >= (game.board_size.y + 2)) {
		return false;
	}
	return true;
}
static void move_snake_once(coords_d target, bool with_apple) {
	if(with_apple == true) {
		if(game.snake.len >= game.snake.max_len) {
			increase_snake_arr(SNAKE_ARR_INCREMENT_STEP);
		}
		game.snake.len++;
		spawn_new_apple();
	}
	for(size_t i = game.snake.len - 1;i >= 1;i--) {
		game.snake.pos[i] = game.snake.pos[i - 1];
	}
	game.snake.pos[0] = target;
}
static void render_board(bool redraw_all) {
	printf("rendered lol\n");
}
static void spawn_new_apple(void) {
	
}
