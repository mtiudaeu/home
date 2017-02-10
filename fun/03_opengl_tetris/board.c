#include "03_opengl_tetris/board.h"

#include "03_opengl_tetris/piece.h"

#include "common/log/log.h"

#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

//MDTMP all this should probably not be a singleton
//--------------------------------------------------------------------------------
// static members

// grid size
static size_t grid_position_x_max = 10;
static size_t grid_position_y_max = 20;

// left over block on the board
#define array_block_max_size 200
static struct grid_position array_block_position[array_block_max_size];
static enum tetris_piece_type array_block_type[array_block_max_size];
static size_t array_block_size = 0;

// current moving piece
#define current_block_max_size 4 // MDTMP get value from piece object.

static struct tetris_piece_desc current_piece_desc;
static struct tetris_piece_desc new_piece_desc;

static struct tetris_piece_blocks current_piece_blocks;
static struct tetris_piece_blocks new_piece_blocks;

static struct grid_position current_array_block_position[current_block_max_size];
static struct grid_position new_array_block_position[current_block_max_size];


//--------------------------------------------------------------------------------
// private methods
static size_t board_check_collision_and_move();
static void board_current_piece_reset();

//--------------------------------------------------------------------------------
static size_t board_check_collision_and_move()
{
  enum {
    UPDATED = 0,
    NO_CHANGE = 1
  };

  {  // check if out of board
    size_t i;
    for (i = 0; i < tetris_piece_block_nb; ++i) {
      if (new_piece_blocks.blocks[i].x >= grid_position_x_max ||
          new_piece_blocks.blocks[i].y >= grid_position_y_max) {
        return NO_CHANGE;
      }
//MDTMP
/*
      if (new_array_block_position[i].x >= grid_position_x_max ||
          new_array_block_position[i].y >= grid_position_y_max) {
        return NO_CHANGE;
      }
*/
    }
  }

  {  // check collision with block on the board
    size_t i, j;
    for (i = 0; i < array_block_size; ++i) {
      for (j = 0; j < tetris_piece_block_nb; ++j) {
        if (array_block_position[i].x == new_piece_blocks.blocks[j].x &&
            array_block_position[i].y == new_piece_blocks.blocks[j].y) {
          return NO_CHANGE;
        }
//MDTMP
/*
        if (array_block_position[i].x == new_array_block_position[j].x &&
            array_block_position[i].y == new_array_block_position[j].y) {
          return NO_CHANGE;
        }
*/
      }
    }
  }

  {  // update current piece
    current_piece_desc = new_piece_desc;
    current_piece_blocks = new_piece_blocks;

//MDTMP
/*
    memcpy(current_array_block_position, new_array_block_position,
           sizeof(current_array_block_position));
*/
  }

  return UPDATED;
}

//--------------------------------------------------------------------------------
static void board_current_piece_reset()
{
  // piece initial position
  current_piece_desc.position.x = 5;
  current_piece_desc.position.y = 15;

  current_piece_desc.type = rand() % PIECE_NB;
  current_piece_desc.rotation = 0;

  tetris_piece_generate_piece(current_piece_blocks,
                              current_piece_desc);
//MDTMP
/*
  tetris_piece_generate_piece(current_array_block_position,
                              current_piece_desc);
*/
}

//--------------------------------------------------------------------------------
size_t tetris_board_init()
{
  { // init modules
    size_t ret = tetris_piece_init();
    if (!ret) {
      LOG_ERROR("tetris_piece_init");
      return ret;
    }
  }

  { // init game board
    srand(time(NULL));
    board_current_piece_reset();
  }

  return 0;
}

//--------------------------------------------------------------------------------
void tetris_board_uninit()
{
  tetris_piece_uninit();
}

//--------------------------------------------------------------------------------
size_t tetris_board_send_command(enum tetris_board_command cmd)
{
  { // generate new potential position
    new_piece_desc = current_piece_desc;

    switch (cmd) {
      case BOARD_CMD_ROT:
        ++new_piece_desc.rotation;
        if (new_piece_desc.rotation >= PIECE_ROT_NB_MAX) {
          new_piece_desc.rotation = PIECE_ROT_0;
        }
        break;
      case BOARD_CMD_MOV_LEFT:
        --new_piece_desc.position.x;
        break;
      case BOARD_CMD_MOV_RIGHT:
        ++new_piece_desc.position.x;
        break;
      case BOARD_CMD_MOV_DOWN:
        --new_piece_desc.position.y;
        break;
    }
//MDTMP tetris_piece_generate_piece(new_array_block_position, new_piece_desc);
    tetris_piece_generate_piece(new_piece_blocks, new_piece_desc);
  }

  // validate collision and update current position
  return board_check_collision_and_move();
}

//--------------------------------------------------------------------------------
void tetris_board_update()
{
  if (tetris_board_send_command(BOARD_CMD_MOV_DOWN) == 0) {
    return;
  }

  // collision detected -> update board and create new piece.

  {  // add current piece to board
    size_t i;
    for (i = 0; i < tetris_piece_block_nb; ++i) {
      assert(array_block_size <= array_block_max_size);
//MDTMP array_block_position[array_block_size] = current_array_block_position[i];
      array_block_position[array_block_size] = current_piece_blocks.blocks[i];
      array_block_type[array_block_size] = current_piece_desc.type;
      ++array_block_size;
    }
  }

  {  // detect tetris
    size_t block_nb_per_line[grid_position_y_max];  // array index is line
                                                    // number.

    {  // initialize array to 0
      size_t line_nb;
      for (line_nb = 0; line_nb < grid_position_y_max; ++line_nb) {
        block_nb_per_line[line_nb] = 0;
      }
    }

    { // check number of blocks per line
      size_t i;
      for (i = 0; i < array_block_size; ++i) {
        const size_t line_nb = array_block_position[i].y;
        assert(line_nb < grid_position_y_max);
        ++block_nb_per_line[line_nb];
      }
    }

    {  // remove complete lines
      size_t line_nb;
      for (line_nb = 0; line_nb < grid_position_y_max; ++line_nb) {
        if (block_nb_per_line[line_nb] != grid_position_x_max) {
          continue;
        }

        { // we have a tetris, remove all blocks of that line
          size_t i;
          for (i = 0; i < array_block_size; ++i) {
            if (array_block_position[i].y != line_nb) {
              continue;
            }

            // remove one block at pos i
            size_t j;
            for (j = i; j < array_block_size - 1; ++j) {
              // move all other blocks to the left
              array_block_position[j] = array_block_position[j + 1];
              array_block_type[j] = array_block_type[j + 1];
            }
            --array_block_size;
            --i;  // recheck same index which is a new block
          }
        }

        { // move all block above that line down.
          size_t i;
          for (i = 0; i < array_block_size; ++i) {
            if (array_block_position[i].y > line_nb) {
              --array_block_position[i].y;
            }
          }
        }
      }
    }
  }

  {  // create new piece
    board_current_piece_reset();
  }
}

//--------------------------------------------------------------------------------
void tetris_board_draw()
{

  // draw all left over block.
  tetris_piece_draw_blocks(array_block_position, array_block_type, array_block_size);
  // draw current moving piece.
//MDTMP tetris_piece_draw_piece(current_array_block_position, current_piece_desc, tetris_piece_block_nb);
  tetris_piece_draw_piece(current_piece_blocks, current_piece_desc);
}
