#include "tetris/board.h"

#include "tetris/piece.h"

#include "graphics/ui_text.h"

#include "common/log/log.h"

#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------
// static members
static struct graphics_ui_text* graphics_ui_text_next_piece = 0x0;
static struct graphics_ui_text* graphics_ui_text_score = 0x0;
static struct graphics_ui_text* graphics_ui_text_score_level = 0x0;
static size_t score = 0;
static size_t score_level = 0;


// grid size
static size_t grid_position_x_max = 10;
static size_t grid_position_y_max = 20;

// left over block on the board
#define array_block_max_size 200
static struct grid_position array_block_position[array_block_max_size];
static enum tetris_piece_type array_block_type[array_block_max_size];
static size_t array_block_size = 0;

// current moving piece
static struct tetris_piece_desc current_piece_desc;
static struct tetris_piece_blocks current_piece_blocks;

static struct tetris_piece_desc next_piece_desc;
static struct tetris_piece_blocks next_piece_blocks;

//--------------------------------------------------------------------------------
static void board_current_piece_reset() {
  // piece initial position
  current_piece_desc.position.x = 5;
  current_piece_desc.position.y = 15;

  current_piece_desc.type = next_piece_desc.type;
  next_piece_desc.type = rand() % PIECE_NB;

  current_piece_desc.rotation = 0;

  tetris_piece_generate_piece(&current_piece_blocks, current_piece_desc);
  tetris_piece_generate_piece(&next_piece_blocks, next_piece_desc);
}

//--------------------------------------------------------------------------------
size_t tetris_board_init() {
  {  // init modules
    size_t ret = tetris_piece_init();
    if (!ret) {
      LOG_ERROR("tetris_piece_init");
      return ret;
    }
  }

  {  // init text ui
    const float ui_scale = 0.8f;

    graphics_ui_text_next_piece = graphics_ui_text_new();
    if (!graphics_ui_text_next_piece) {
      LOG_ERROR("!graphics_ui_text_next_piece");
      return 1;
    }

    graphics_ui_text_set_scale(graphics_ui_text_next_piece, ui_scale);
    struct graphics_coord_2d position = {0.05, 0.82};
    graphics_ui_text_set_position(graphics_ui_text_next_piece, position);
    graphics_ui_text_set_msg(graphics_ui_text_next_piece, "next piece");

    graphics_ui_text_score = graphics_ui_text_new();
    if (!graphics_ui_text_score) {
      LOG_ERROR("!graphics_ui_text_score");
      return 1;
    }
    graphics_ui_text_set_scale(graphics_ui_text_score, ui_scale);
    position.y = 0.2f;
    graphics_ui_text_set_position(graphics_ui_text_score, position);
    graphics_ui_text_set_msg(graphics_ui_text_score, "score : 0");

    graphics_ui_text_score_level = graphics_ui_text_new();
    if (!graphics_ui_text_score) {
      LOG_ERROR("!graphics_ui_text_score");
      return 1;
    }
    graphics_ui_text_set_scale(graphics_ui_text_score_level, ui_scale);
    position.y = 0.1f;
    graphics_ui_text_set_position(graphics_ui_text_score_level, position);
    graphics_ui_text_set_msg(graphics_ui_text_score_level, "level : 0");
  }

  {  // init game board pieces
    srand(time(NULL));
    next_piece_desc.type = rand() % PIECE_NB;
    next_piece_desc.rotation = 0;
    next_piece_desc.position.x = 12;
    next_piece_desc.position.y = 14;

    board_current_piece_reset();
  }

  return 0;
}

//--------------------------------------------------------------------------------
void tetris_board_uninit() {
{
    graphics_ui_text_delete(graphics_ui_text_next_piece);
    graphics_ui_text_next_piece = 0x0;

    graphics_ui_text_delete(graphics_ui_text_score);
    graphics_ui_text_score = 0x0;

    graphics_ui_text_delete(graphics_ui_text_score_level);
    graphics_ui_text_score_level = 0x0;
}
 tetris_piece_uninit();
 }

//--------------------------------------------------------------------------------
size_t tetris_board_send_command(enum tetris_board_command cmd) {
  struct tetris_piece_desc new_piece_desc = current_piece_desc;
  struct tetris_piece_blocks new_piece_blocks;

  {  // generate new blocks position
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
    tetris_piece_generate_piece(&new_piece_blocks, new_piece_desc);
  }

  {  // validate collision and update current position
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
        }
      }
    }

    {  // update current piece
      current_piece_desc = new_piece_desc;
      current_piece_blocks = new_piece_blocks;
    }

    return UPDATED;
  }
}

//--------------------------------------------------------------------------------
void tetris_board_update(const float time_delta) {
  static float time_until_last_update = 0.0f;
  static float time_update_frequency = 1.0f;
  time_until_last_update += time_delta;

  if (time_until_last_update < time_update_frequency) {
    return;
  }
  time_until_last_update -= time_update_frequency;

  if (tetris_board_send_command(BOARD_CMD_MOV_DOWN) == 0) {
    return;
  }

  // collision detected -> update board and create new piece.

  {  // add current piece to board
    size_t i;
    for (i = 0; i < tetris_piece_block_nb; ++i) {
      assert(array_block_size <= array_block_max_size);
      array_block_position[array_block_size] = current_piece_blocks.blocks[i];
      array_block_type[array_block_size] = current_piece_desc.type;
      ++array_block_size;
    }
  }

  {                                                 // detect tetris
    size_t block_nb_per_line[grid_position_y_max];  // array index is line
                                                    // number.

    {  // initialize array to 0
      size_t line_nb;
      for (line_nb = 0; line_nb < grid_position_y_max; ++line_nb) {
        block_nb_per_line[line_nb] = 0;
      }
    }

    {  // check number of blocks per line
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
        // we have a tetris!
        {  // increase score
           score += 1000;
           char score_text[1000];
           score_text[0] = 0;
           snprintf(score_text, 1000, "score : %zu", score);
           graphics_ui_text_set_msg(graphics_ui_text_score, score_text);

           const size_t next_score_level = score / 10000;
           if (score_level != next_score_level) {
             time_update_frequency *= 0.75f;
           }
           score_level = next_score_level;
           char score_level_text[1000];
           score_level_text[0] = 0;
           snprintf(score_level_text, 1000, "level : %zu", score_level);
           graphics_ui_text_set_msg(graphics_ui_text_score_level, score_level_text);
        }

        {  // remove all blocks of that line
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

        {  // move all block above that line down.
          size_t i;
          for (i = 0; i < array_block_size; ++i) {
            if (array_block_position[i].y > line_nb) {
              --array_block_position[i].y;
            }
          }
          for (i = line_nb; i < grid_position_y_max-1; ++i) {
            block_nb_per_line[i] = block_nb_per_line[i+1]; 
          }
          block_nb_per_line[grid_position_y_max] = 0;

          --line_nb; // recheck same line index which is a new line that was moved down
        }
      }
    }
  }

  {  // create new piece
    board_current_piece_reset();
  }
}

//--------------------------------------------------------------------------------
void tetris_board_draw() {

  // draw all left over block.
  tetris_piece_draw_blocks(array_block_position, array_block_type,
                           array_block_size);
  // draw current moving piece.
  tetris_piece_draw_piece(current_piece_blocks, current_piece_desc);
  // draw preview of next piece.
  tetris_piece_draw_piece(next_piece_blocks, next_piece_desc);

  // draw text
  {
    assert(graphics_ui_text_next_piece);
    graphics_ui_text_draw(graphics_ui_text_next_piece);

    assert(graphics_ui_text_score);
    graphics_ui_text_draw(graphics_ui_text_score);

    assert(graphics_ui_text_score_level);
    graphics_ui_text_draw(graphics_ui_text_score_level);
}
}
