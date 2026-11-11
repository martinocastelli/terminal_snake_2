#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include "renderer.h"
#include "tc.h"

static char output[BOARD_SIZE_X + 2][BOARD_SIZE_Y + 2];

void sigint_handler(int sig);
static void print_char(char c, uint16_t x, uint16_t y);

void init_renderer() {
	signal(SIGINT, sigint_handler);
	tc_init();
	tc_set_echo_mode(false);
	tc_set_canonical_mode(false);
	tc_hide_cursor(true);

	for(size_t x = 0;x < BOARD_SIZE_X + 2;x++) {
		for(size_t y = 0;y < BOARD_SIZE_Y + 2;y++) {
			output[x][y] = 0;
		}
	}


	tc_erase_to_origin();
	for(size_t i = 0;i < BOARD_SIZE_X + 2;i++) {
		print_char('#', i, 0);
		print_char('#', i, BOARD_SIZE_Y + 1);

	}
	for(size_t i = 0;i < BOARD_SIZE_Y + 2;i++) {
		print_char('#', 0, i);
		print_char('#', BOARD_SIZE_X + 1, i);
	}
}

void end_renderer() {
	tc_restore_defaults();

	tc_hide_cursor(false);

	tc_erase_to_origin();
	fflush(stdout);
}

void render_board(cell_type_e board[BOARD_SIZE_X][BOARD_SIZE_Y]) {
	for(size_t x = 0;x < BOARD_SIZE_X;x++) {
		for(size_t y = 0;y < BOARD_SIZE_Y;y++) {
			switch(board[x][y]) {
				case SNAKE_HEAD:
					print_char('0', x + 1, y + 1);
					break;
				case SNAKE:
					print_char('o', x + 1, y + 1);
					break;
				case APPLE:
					print_char('@', x + 1, y + 1);
					break;
				default:
					print_char(' ', x + 1, y + 1);
			}
		}
	}
	putchar('\n');
	fflush(stdout);
}

void sigint_handler(int sig) {
	(void)sig;
	printf("exiting with SIGINT\n");

	end_renderer();

	_exit(0);
}

void print_char(char c, uint16_t x, uint16_t y) {
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
