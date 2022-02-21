#include "tetris/piece.h"


#include "tetris/piece.private.h"

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
static void internal_rectangle_2D_set_texture(
    struct rectangle_2d* const rectangle_2D, const enum tetris_piece_type type) {
  assert(rectangle_2D);
  assert(type < PIECE_NB);
  static const float texture_increment_x = 1.0f / 8.0f;
  static const float texture_increment_y = 1.0f;
  rectangle_2D->width = texture_increment_x;
  rectangle_2D->height = texture_increment_y;
  rectangle_2D->x = (type * texture_increment_x);
  rectangle_2D->y = texture_increment_y;
}

//--------------------------------------------------------------------------------
size_t tetris_piece_init() {
  if (!internal_bo_texture) {
    const char* tileset_filename = "common/assets/tmp/tetris.png";
    internal_bo_texture =
        graphics_shader_texture_buffer_create(tileset_filename);
  }
  return internal_bo_texture;
}

//--------------------------------------------------------------------------------
void tetris_piece_uninit() { glDeleteTextures(1, &internal_bo_texture); }

//--------------------------------------------------------------------------------
void tetris_piece_draw_blocks(struct grid_position* const array_block_position,
                              enum tetris_piece_type* const array_block_type,
                              size_t length) {
  struct rectangle_2d array_context_position[length];
  struct rectangle_2d array_texture_position[length];

  size_t i;
  for (i = 0; i < length; ++i) {
    array_context_position[i].width = internal_block_width;
    array_context_position[i].height = internal_block_height;
    array_context_position[i].x =
        -1.0f + ((float)array_block_position[i].x * internal_block_width);
    array_context_position[i].y =
        -1.0f + ((float)array_block_position[i].y * internal_block_height);
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
void tetris_piece_draw_piece(struct tetris_piece_blocks tetris_piece_blocks,
                             struct tetris_piece_desc tetris_piece_desc) {

  enum tetris_piece_type array_block_type[tetris_piece_block_nb];
  size_t i;
  for (i = 0; i < tetris_piece_block_nb; ++i) {
    array_block_type[i] = tetris_piece_desc.type;
  }
  tetris_piece_draw_blocks(tetris_piece_blocks.blocks, array_block_type,
                           tetris_piece_block_nb);
}

//--------------------------------------------------------------------------------
void tetris_piece_generate_piece(
    struct tetris_piece_blocks* const tetris_piece_blocks,
    const struct tetris_piece_desc tetris_piece_desc) {
  assert(tetris_piece_blocks);

  switch (tetris_piece_desc.type) {
    case PIECE_LINE: {
      draw_piece_line(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_L_LEFT: {
      draw_piece_l_left(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_L_RIGHT: {
      draw_piece_l_right(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_SQUARE: {
      draw_piece_square(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_Z_LEFT: {
      draw_piece_z_left(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_T: {
      draw_piece_t(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_Z_RIGHT: {
      draw_piece_z_right(tetris_piece_blocks, tetris_piece_desc);
    } break;
    case PIECE_NB:
      assert(0);  // invalid case
  }
}
