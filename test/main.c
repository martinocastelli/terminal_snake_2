#include <stdio.h>
#include <unistd.h>
#include "tc/tc.h"

int main(void) {
	tc_init();
	tc_set_canonical_mode(false);
	tc_set_echo_mode(false);

	tc_keyboard_input_d buff;
	do {
		sleep(1);
		tc_erase_to_origin();
		tc_get_pressed_keys(&buff);
		printf("%d", buff.escape_input[buff.escape_input_size - 1]);
		fflush(stdout);
	} while(buff.normal_input[0] != 'q');

	tc_restore_defaults();

	return 0;
}
