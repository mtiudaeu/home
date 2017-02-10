#include "03_opengl_tetris/piece.h"

#include "common/graphics/primitive/rectangle_2D.h"

#include "common/graphics/shader.h"

#include <assert.h>
#include <stdlib.h>

//--------------------------------------------------------------------------------
// static members
static const size_t internal_pieces_block_nb = 4;
static const float internal_block_width = 0.1f;
static const float internal_block_height = 0.1f;

static GLuint internal_bo_texture = 0;

static size_t grid_position_x_max = 10;
static size_t grid_position_y_max = 100;

//--------------------------------------------------------------------------------
// private methods
static void internal_rectangle_2D_set_texture(Rectangle2D* const rectangle_2D,
                                              const enum tetris_piece_type type);

//--------------------------------------------------------------------------------
static void internal_rectangle_2D_set_texture(Rectangle2D* const rectangle_2D,
                                       const enum tetris_piece_type type) {
  assert(rectangle_2D);

  static const float texture_increment_x = 1.0f / 15.0f;
  static const float texture_increment_y = 1.0f / 5.0f;
  rectangle_2D->width = texture_increment_x;
  rectangle_2D->height = texture_increment_y;

  switch (type) {
    case PIECE_LINE:
      rectangle_2D->x = (1.0f * texture_increment_x);
      rectangle_2D->y = (3.0f * texture_increment_y);
      break;
    case PIECE_L_LEFT:
      rectangle_2D->x = (5.0f * texture_increment_x);
      rectangle_2D->y = (3.0f * texture_increment_y);
      break;
    case PIECE_L_RIGHT:
      rectangle_2D->x = (9.0f * texture_increment_x);
      rectangle_2D->y = (3.0f * texture_increment_y);
      break;
    case PIECE_SQUARE:
      rectangle_2D->x = (13.0f * texture_increment_x);
      rectangle_2D->y = (3.0f * texture_increment_y);
      break;
    case PIECE_Z_LEFT:
      rectangle_2D->x = (2.0f * texture_increment_x);
      rectangle_2D->y = 0.0f;
      break;
    case PIECE_T:
      rectangle_2D->x = (6.0f * texture_increment_x);
      rectangle_2D->y = 0.0f;
      break;
    case PIECE_Z_RIGHT:
      rectangle_2D->x = (11.0f * texture_increment_x);
      rectangle_2D->y = 0.0f;
      break;
    case PIECE_NB:
      assert(0); // invalid case
  }

/*
  size_t i;
  for (i = 1; i < internal_pieces_block_nb; ++i) {
    rectangle_2D[i].width = rectangle_2D->width;
    rectangle_2D[i].height = rectangle_2D->height;
    rectangle_2D[i].x = rectangle_2D->x;
    rectangle_2D[i].y = rectangle_2D->y;
  }
*/
}

//--------------------------------------------------------------------------------
size_t tetris_piece_init()
{
  if (!internal_bo_texture) {
    const char* tileset_filename = "common/assets/tmp/tetris_texture.png";
    internal_bo_texture =
        graphics_shader_texture_buffer_create(tileset_filename);
  }
  return internal_bo_texture;
}

//--------------------------------------------------------------------------------
void tetris_piece_uninit()
{
  glDeleteTextures(1, &internal_bo_texture);
}

//--------------------------------------------------------------------------------
void tetris_piece_draw_blocks(struct grid_position* const array_block_position,
                         enum tetris_piece_type* const array_block_type,
                         size_t length) {
  Rectangle2D array_context_position[length];
  Rectangle2D array_texture_position[length];

  size_t i;
  for (i = 0; i < length; ++i) {
    array_context_position[i].width = internal_block_width;
    array_context_position[i].height = internal_block_height;
    array_context_position[i].x = -1.0f + ((float)array_block_position[i].x * internal_block_width);
    array_context_position[i].y = -1.0f + ((float)array_block_position[i].y * internal_block_height);
  }
  for (i = 0; i < length; ++i) {
    internal_rectangle_2D_set_texture(&array_texture_position[i],
                                      array_block_type[i]);
  }

  assert(internal_bo_texture);
  graphics_primitive_rectangle_2D_draw(internal_bo_texture,
                                       array_context_position,
                                       array_texture_position, length);
}

//--------------------------------------------------------------------------------
void tetris_piece_draw_piece(
    struct tetris_piece_blocks tetris_piece_blocks,
                       struct tetris_piece_desc tetris_piece_desc ){

  enum tetris_piece_type array_block_type[tetris_piece_block_nb];
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    array_block_type[i] = tetris_piece_desc.type;
  }
  tetris_piece_draw_blocks(tetris_piece_blocks.blocks, array_block_type, tetris_piece_block_nb);
}

//--------------------------------------------------------------------------------
void tetris_piece_generate_piece(
    struct tetris_piece_blocks tetris_piece_blocks,
                                 const struct tetris_piece_desc tetris_piece_desc) {
  // MDTMP finish rotation for every one.

  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    tetris_piece_blocks.blocks[i].x = tetris_piece_desc.position.x;
    tetris_piece_blocks.blocks[i].y = tetris_piece_desc.position.y;
  }

  switch (tetris_piece_desc.type) {
    case PIECE_LINE: {
      if (tetris_piece_desc.rotation % 2) {
        for (i = 1; i < tetris_piece_block_nb; ++i) {
          tetris_piece_blocks.blocks[i].x += i;
        }
      } else {
        for (i = 1; i < tetris_piece_block_nb; ++i) {
          tetris_piece_blocks.blocks[i].y += i;
        }
      }
    } break;
    case PIECE_L_LEFT: {
      // horizontal line of 3
      for (i = 1; i < tetris_piece_block_nb - 1; ++i) {
        tetris_piece_blocks.blocks[i].x += i;
      }
      // + 1 top left
      ++tetris_piece_blocks.blocks[3].y;
    } break;
    case PIECE_L_RIGHT: {
      // horizontal line of 3
      for (i = 1; i < tetris_piece_block_nb - 1; ++i) {
        tetris_piece_blocks.blocks[i].x += i;
      }
      // + 1 top right
      tetris_piece_blocks.blocks[3].x = tetris_piece_blocks.blocks[2].x;
      ++tetris_piece_blocks.blocks[3].y;
    } break;
    case PIECE_SQUARE: {
      ++tetris_piece_blocks.blocks[1].x;
      ++tetris_piece_blocks.blocks[2].y;
      ++tetris_piece_blocks.blocks[3].x;
      ++tetris_piece_blocks.blocks[3].y;
    } break;
    case PIECE_Z_LEFT: {
      ++tetris_piece_blocks.blocks[1].x;
      tetris_piece_blocks.blocks[2].x = tetris_piece_blocks.blocks[1].x;
      ++tetris_piece_blocks.blocks[2].y;
      tetris_piece_blocks.blocks[3].x = tetris_piece_blocks.blocks[2].x + 1;
      tetris_piece_blocks.blocks[3].y = tetris_piece_blocks.blocks[2].y;
    } break;
    case PIECE_T: {
      // horizontal line of 3
      for (i = 1; i < tetris_piece_block_nb - 1; ++i) {
        tetris_piece_blocks.blocks[i].x += i;
      }
      // + 1 top middle
      ++tetris_piece_blocks.blocks[3].x;
      ++tetris_piece_blocks.blocks[3].y;
    } break;
    case PIECE_Z_RIGHT: {
      ++tetris_piece_blocks.blocks[0].y;
      tetris_piece_blocks.blocks[1].y = tetris_piece_blocks.blocks[0].y;
      ++tetris_piece_blocks.blocks[1].x;
      tetris_piece_blocks.blocks[2].x = tetris_piece_blocks.blocks[1].x;
      tetris_piece_blocks.blocks[3].x = tetris_piece_blocks.blocks[2].x + 1;
    } break;
    case PIECE_NB:
      assert(0);  // invalid case
  }
}
