#include <stdio.h>

#include "game.h"

int main() {
	uint16_t score = play_game();


	printf("fool, you lost with just %u points\n", score);

	return 0;
}
