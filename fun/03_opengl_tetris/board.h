#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <stddef.h>

size_t tetris_board_init();
void tetris_board_uninit();

void tetris_board_update();
void tetris_board_draw();

#endif // TETRIS_BOARD_H

