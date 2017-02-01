#include "03_opengl_tetris/board.h"

#include "03_opengl_tetris/piece.h"

static size_t grid_position_x_max = 10;
static size_t grid_position_y_max = 100;

#define array_block_max_size 1000
static struct grid_position array_block_position[array_block_max_size];
static TetrisPieceType array_block_type[array_block_max_size];
static size_t array_block_size = 0;

//MDTMP hardcode 4?
static TetrisPieceType current_block_type[4];
static struct grid_position current_piece_position;
static TetrisPieceRotation current_piece_rotation;
static struct grid_position current_array_block_position[4];

static struct grid_position new_piece_position;
static TetrisPieceRotation new_piece_rotation;
static struct grid_position new_array_block_position[4];



static size_t tmp_init = 0;

//--------------------------------------------------------------------------------
static void internal_check_collision_and_move()
{
  // check if out of board
  if (new_piece_position.x > grid_position_x_max ||
      new_piece_position.y > grid_position_y_max) {
    return;
  }

  {  // check collision with block on the board
    size_t i, j;
    for (i = 0; i < array_block_size; ++i) {
      for (j = 0; j < 4; ++j) {
        if (array_block_position[i].x == new_array_block_position[j].x &&
            array_block_position[i].y == new_array_block_position[j].y) {
          return;
        }
      }
    }
  }

  {  // update current piece
    current_piece_position = new_piece_position;
    tetris_piece_generate_4_blocks(
        current_array_block_position, current_piece_position,
        current_block_type[0], current_piece_rotation);
  }
}

//--------------------------------------------------------------------------------
void tetris_board_update()
{
  { // set future position
    new_piece_position = current_piece_position;
    --new_piece_position.y;
    new_piece_rotation = current_piece_rotation;
    tetris_piece_generate_4_blocks(
        new_array_block_position, new_piece_position,
        current_block_type[0], new_piece_rotation);
  }

  // validate collision
  internal_check_collision_and_move();
}

//--------------------------------------------------------------------------------
void tetris_board_draw()
{
  if (!tmp_init) {
    tmp_init = 1;

    array_block_position[0].x = 0;
    array_block_position[0].y = 0;
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
    array_block_size = 4;

    current_piece_position.x = 5;
    current_piece_position.y = 15;
    current_block_type[0] = 1;
    current_block_type[1] = 1;
    current_block_type[2] = 1;
    current_block_type[3] = 1;
    current_piece_rotation = 0;
    tetris_piece_generate_4_blocks(current_array_block_position,
                                   current_piece_position, current_block_type[0],
                                   current_piece_rotation);
  }

  // draw all left over block.
  tetris_piece_draw_2(array_block_position, array_block_type, array_block_size);
  // draw current moving piece.
  tetris_piece_draw_2(current_array_block_position, current_block_type, 4);
}
