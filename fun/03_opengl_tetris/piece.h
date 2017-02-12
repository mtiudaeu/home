#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include "common/graphics/point.h"

#include <stddef.h>
#include <assert.h>

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
  PIECE_Z_RIGHT,
  PIECE_NB
};

enum tetris_piece_rotation {
  PIECE_ROT_0,
  PIECE_ROT_1,
  PIECE_ROT_2,
  PIECE_ROT_3,
  PIECE_ROT_NB_MAX
};

struct tetris_piece_desc {
  enum tetris_piece_type type;
  enum tetris_piece_rotation rotation;
  struct grid_position position;
};

#define tetris_piece_block_nb 4
struct tetris_piece_blocks {
  struct grid_position blocks[tetris_piece_block_nb];
};

//--------------------------------------------------------------------------------
// public interface
size_t tetris_piece_init();
void tetris_piece_uninit();

void tetris_piece_draw_blocks(struct grid_position* const array_block_position,
                              enum tetris_piece_type* const array_block_type,
                              size_t length);
void tetris_piece_draw_piece(struct tetris_piece_blocks tetris_piece_blocks,
                             struct tetris_piece_desc tetris_piece_desc);

void tetris_piece_generate_piece(struct tetris_piece_blocks * const tetris_piece_blocks,
                                 const struct tetris_piece_desc);

#endif  // TETRIS_PIECE_H
