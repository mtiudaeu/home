#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <stddef.h>

enum tetris_board_command {
  BOARD_CMD_ROT,
  BOARD_CMD_MOV_LEFT,
  BOARD_CMD_MOV_RIGHT,
  BOARD_CMD_MOV_DOWN
};

size_t tetris_board_init();
void tetris_board_uninit();

size_t tetris_board_send_command(enum tetris_board_command cmd);

void tetris_board_update(const float time_delta);
void tetris_board_draw();

#endif // TETRIS_BOARD_H

