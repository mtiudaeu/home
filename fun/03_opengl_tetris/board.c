#include "03_opengl_tetris/board.h"

#include "03_opengl_tetris/piece.h"

#include "common/log/log.h"

#include <string.h>
#include <assert.h>

//MDTMP all this should probably not be a singleton
//--------------------------------------------------------------------------------
// static members

// grid size
static size_t grid_position_x_max = 10;
static size_t grid_position_y_max = 100;

// left over block on the board
#define array_block_max_size 1000
static struct grid_position array_block_position[array_block_max_size];
static enum tetris_piece_type array_block_type[array_block_max_size];
static size_t array_block_size = 0;

// current moving piece
#define current_block_max_size 4 // MDTMP get value from piece object.
static enum tetris_piece_type current_block_type[current_block_max_size];

static struct grid_position current_piece_position;
static struct grid_position new_piece_position;

static enum tetris_piece_rotation current_piece_rotation;
static struct grid_position current_array_block_position[current_block_max_size];

static enum tetris_piece_rotation new_piece_rotation;
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
    for (i = 0; i < current_block_max_size; ++i) {
      if (new_array_block_position[i].x > grid_position_x_max ||
          new_array_block_position[i].y > grid_position_y_max) {
        return NO_CHANGE;
      }
    }
  }

  {  // check collision with block on the board
    size_t i, j;
    for (i = 0; i < array_block_size; ++i) {
      for (j = 0; j < current_block_max_size; ++j) {
        if (array_block_position[i].x == new_array_block_position[j].x &&
            array_block_position[i].y == new_array_block_position[j].y) {
          return NO_CHANGE;
        }
      }
    }
  }

  {  // update current piece
    current_piece_position = new_piece_position;
    current_piece_rotation = new_piece_rotation;
    memcpy(current_array_block_position, new_array_block_position,
           sizeof(current_array_block_position));
  }

  return UPDATED;
}

//--------------------------------------------------------------------------------
static void board_current_piece_reset()
{
  // piece initial position
  current_piece_position.x = 5;
  current_piece_position.y = 15;

  const int type = rand() % PIECE_NB;
  size_t i;
  for (i = 0; i < current_block_max_size; ++i) {
    current_block_type[i] = type;
  }
  current_piece_rotation = 0;

  tetris_piece_generate_piece(current_array_block_position,
                              current_piece_position, current_block_type[0],
                              current_piece_rotation);
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
    new_piece_position = current_piece_position;
    new_piece_rotation = current_piece_rotation;

    switch (cmd) {
      case BOARD_CMD_ROT:
        ++new_piece_rotation;
        if (new_piece_rotation >= PIECE_ROT_NB_MAX) {
          new_piece_rotation = PIECE_ROT_0;
        }
        break;
      case BOARD_CMD_MOV_LEFT:
        --new_piece_position.x;
        break;
      case BOARD_CMD_MOV_RIGHT:
        ++new_piece_position.x;
        break;
      case BOARD_CMD_MOV_DOWN:
        --new_piece_position.y;
        break;
    }
    tetris_piece_generate_piece(new_array_block_position, new_piece_position,
                                current_block_type[0], new_piece_rotation);
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

  // collision detected, update board and create new piece.
  size_t i;
  for (i = 0; i < current_block_max_size; ++i) {
    // MDTMP array_block_size
    // MDTMP array_block_max_size

    assert(array_block_size > array_block_max_size);
    array_block_position[array_block_size] = current_array_block_position[i];
    array_block_type[array_block_size] = current_block_type[i];
    ;
    ++array_block_size;
  }

  //MDTMP detect tetris.
  //MDTMP create new piece.
  board_current_piece_reset();

}

//--------------------------------------------------------------------------------
void tetris_board_draw()
{

  // draw all left over block.
  tetris_piece_draw(array_block_position, array_block_type, array_block_size);
  // draw current moving piece.
  tetris_piece_draw(current_array_block_position, current_block_type, 4);
}
