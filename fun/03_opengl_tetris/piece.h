#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include "common/graphics/point.h"

#include <stddef.h>

//--------------------------------------------------------------------------------
// public data
struct grid_position {
  size_t x;
  size_t y;
};

enum tetris_piece_type {
  PIECE_LINE,
  PIECE_L_LEFT,
  PIECE_L_RIGHT,
  PIECE_SQUARE,
  PIECE_Z_LEFT,
  PIECE_T,
  PIECE_Z_RIGHT
};

enum tetris_piece_rotation {
  PIECE_ROT_0,
  PIECE_ROT_1,
  PIECE_ROT_2,
  PIECE_ROT_3,
  PIECE_ROT_NB_MAX
};

//--------------------------------------------------------------------------------
// public interface
size_t tetris_piece_init();
void tetris_piece_uninit();

void tetris_piece_draw(struct grid_position* const array_block_position,
                         enum tetris_piece_type* const array_block_type,
                         size_t length);

void tetris_piece_generate_piece(struct grid_position block_position[4],
                                    const struct grid_position piece_position,
                                    const enum tetris_piece_type type,
                                    const enum tetris_piece_rotation rotation);

#endif // TETRIS_PIECE_H
