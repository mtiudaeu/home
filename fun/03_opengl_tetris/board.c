#include "03_opengl_tetris/board.h"

#include "03_opengl_tetris/piece.h"

static size_t grid_position_x_max = 10;
static size_t grid_position_y_max = 100;

#define array_block_max_size 1000
static struct grid_position array_block_position[array_block_max_size];
static TetrisPieceType array_block_type[array_block_max_size];
static size_t array_block_size = 0;

static TetrisPieceType current_block_type;
static struct grid_position current_piece_position;
static TetrisPieceRotation current_piece_rotation;
//MDTMP hardcode 4?
static struct grid_position current_array_block_position[4];


static size_t tmp_init = 0;

void tetris_board_draw()
{
  if (!tmp_init) {
    array_block_position[0].x = 0;
    array_block_position[0].y = 1;
    array_block_position[1].x = 5;
    array_block_position[1].y = 10;
    array_block_position[2].x = 3;
    array_block_position[2].y = 9;
    array_block_position[3].x = 2;
    array_block_position[3].y = 3;

    array_block_type[0] = 0;
    array_block_type[1] = 1;
    array_block_type[2] = 2;
    array_block_type[3] = 3;

    tmp_init = 1;
    array_block_size = 4;
  }

  tetris_piece_draw_2(array_block_position, array_block_type, array_block_size);
}
