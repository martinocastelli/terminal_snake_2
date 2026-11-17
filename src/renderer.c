#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "renderer.h"
#include "tc.h"

#ifndef ENABLE_MULTIPLE_BOARD
static char output[BOARD_SIZE_X + 2][BOARD_SIZE_Y + 2];
#else //ENABLE_MULTIPLE_BOARD
static char output[2 * BOARD_SIZE_X + 2][2 * BOARD_SIZE_Y + 2];
#endif //ENABLE_MULTIPLE_BOARD

void sigint_handler(int sig);
static inline void print_char(char c, uint16_t x, uint16_t y);

void init_renderer() {
	signal(SIGINT, sigint_handler);
	tc_init();
	tc_set_echo_mode(false);
	tc_set_canonical_mode(false);
	tc_hide_cursor(true);

#ifndef ENABLE_MULTIPLE_BOARD
	for(size_t x = 0;x < BOARD_SIZE_X + 2;x++) {
		for(size_t y = 0;y < BOARD_SIZE_Y + 2;y++) {
			output[x][y] = 0;
		}
	}
#else //ENABLE_MULTIPLE_BOARD
	for(size_t x = 0;x < 2 * BOARD_SIZE_X + 2;x++) {
		for(size_t y = 0;y < 2 * BOARD_SIZE_Y + 2;y++) {
			output[x][y] = 0;
		}
	}
#endif //ENABLE_MULTIPLE_BOARD


	tc_erase_to_origin();
#ifndef ENABLE_MULTIPLE_BOARD
	for(size_t i = 0;i < BOARD_SIZE_X + 2;i++) {
		print_char('#', i, 0);
		print_char('#', i, BOARD_SIZE_Y + 1);
	}
	for(size_t i = 0;i < BOARD_SIZE_Y + 2;i++) {
		print_char('#', 0, i);
		print_char('#', BOARD_SIZE_X + 1, i);
	}
#else //ENABLE_MULTIPLE_BOARD
	for(size_t i = 0;i < 2 * BOARD_SIZE_X + 2;i++) {
		print_char('#', i, 0);
		print_char('#', i, 2 * BOARD_SIZE_Y + 1);
	}
	for(size_t i = 0;i < 2 * BOARD_SIZE_Y + 2;i++) {
		print_char('#', 0, i);
		print_char('#', 2 * BOARD_SIZE_X + 1, i);
	}
#endif //ENABLE_MULTIPLE_BOARD
}

void end_renderer() {
	tc_restore_defaults();

	tc_hide_cursor(false);

	tc_set_color_default();

	// tc_erase_to_origin();
	fflush(stdout);
}

void render_board(cell_type_e board[BOARD_SIZE_X][BOARD_SIZE_Y], uint16_t score, uint16_t best_score) {
	for(size_t x = 0;x < BOARD_SIZE_X;x++) {
		for(size_t y = 0;y < BOARD_SIZE_Y;y++) {
			switch(board[x][y]) {
				case SNAKE_HEAD:
					print_char('0', x + 1, y + 1);
#ifdef ENABLE_MULTIPLE_BOARD
					print_char('0', x + 1 + BOARD_SIZE_X, y + 1);
					print_char('0', x + 1, y + 1 + BOARD_SIZE_Y);
					print_char('0', x + 1 + BOARD_SIZE_X, y + 1 + BOARD_SIZE_Y);
#endif //ENABLE_MULTIPLE_BOARD
					break;
				case SNAKE:
					print_char('o', x + 1, y + 1);
#ifdef ENABLE_MULTIPLE_BOARD
					print_char('o', x + 1 + BOARD_SIZE_X, y + 1);
					print_char('o', x + 1, y + 1 + BOARD_SIZE_Y);
					print_char('o', x + 1 + BOARD_SIZE_X, y + 1 + BOARD_SIZE_Y);
#endif //ENABLE_MULTIPLE_BOARD
					break;
				case APPLE:
					print_char('@', x + 1, y + 1);
#ifdef ENABLE_MULTIPLE_BOARD
					print_char('@', x + 1 + BOARD_SIZE_X, y + 1);
					print_char('@', x + 1, y + 1 + BOARD_SIZE_Y);
					print_char('@', x + 1 + BOARD_SIZE_X, y + 1 + BOARD_SIZE_Y);
#endif //ENABLE_MULTIPLE_BOARD
					break;
				default:
					print_char(' ', x + 1, y + 1);
#ifdef ENABLE_MULTIPLE_BOARD
					print_char(' ', x + 1 + BOARD_SIZE_X, y + 1);
					print_char(' ', x + 1, y + 1 + BOARD_SIZE_Y);
					print_char(' ', x + 1 + BOARD_SIZE_X, y + 1 + BOARD_SIZE_Y);
#endif //ENABLE_MULTIPLE_BOARD
			}
		}
	}
	tc_set_color_default();
	putchar('\n');
	tc_move_to(1, BOARD_SIZE_X + 3);
	printf("score: %u", score);
	tc_move_to(2, BOARD_SIZE_X + 3);
	printf("best score: %u", best_score);
	fflush(stdout);
}

void sigint_handler(int sig) {
	(void)sig;
	printf("exiting with SIGINT\n");

	end_renderer();

	_exit(0);
}

static inline void print_char(char c, uint16_t x, uint16_t y) {
	if(c != output[x][y]) {
		tc_move_to(y + 1, x + 1);
		switch(c) {
			case '#':
				tc_set_color_standard(TC_BLACK);
				break;
			case '@':
				tc_set_color_standard(TC_RED);
				break;
			case '0':
				tc_set_color_standard(TC_GREEN);
				break;
			case 'o':
				tc_set_color_standard(TC_BLUE);
				break;
			default:
				tc_set_color_standard(TC_COLOR_DEFAULT);
		}
		putchar(c);
		output[x][y] = c;
	}
}
