#ifndef __SNAKE_H__
#define __SNAKE_H__
#include <stdint.h>

#include "../tc/tc.h"

bool snake_game(uint16_t *resul, uint16_t size_x, uint16_t size_y, uint16_t *initial_pos_x, uint16_t *initial_pos_y, size_t initial_len);

#endif //__SNAKE_H__
