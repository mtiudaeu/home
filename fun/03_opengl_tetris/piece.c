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
                                              const TetrisPieceType type);

//--------------------------------------------------------------------------------
static void internal_rectangle_2D_set_texture(Rectangle2D* const rectangle_2D,
                                       const TetrisPieceType type) {
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
void tetris_piece_draw_2(struct grid_position* const array_block_position,
                         TetrisPieceType* const array_block_type,
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
void tetris_piece_generate_4_blocks(struct grid_position block_position[4],
                                    const struct grid_position piece_position,
                                    const TetrisPieceType type,
//MDTMP use rotation
                                    const TetrisPieceRotation rotation) {
  const size_t block_nb = 4;
  size_t i;
  for (i = 0; i < block_nb; ++i) {
    block_position[i].x = piece_position.x;
    block_position[i].y = piece_position.y;
  }

  switch (type) {
    case PIECE_LINE: {
      // horizontal line of 4
      for (i = 1; i < block_nb; ++i) {
        block_position[i].x += i;
      }
    } break;
    case PIECE_L_LEFT: {
      // horizontal line of 3
      for (i = 1; i < block_nb - 1; ++i) {
        block_position[i].x += i;
      }
      // + 1 top left
      ++block_position[3].y;
    } break;
    case PIECE_L_RIGHT: {
      // horizontal line of 3
      for (i = 1; i < block_nb - 1; ++i) {
        block_position[i].x += i;
      }
      // + 1 top right
      block_position[3].x = block_position[2].x;
      ++block_position[3].y;
    } break;
    case PIECE_SQUARE: {
      ++block_position[1].x;
      ++block_position[2].y;
      ++block_position[3].x;
      ++block_position[3].y;
    } break;
    case PIECE_Z_LEFT: {
      ++block_position[1].x;
      block_position[2].x = block_position[1].x;
      ++block_position[2].y;
      block_position[3].x = block_position[2].x + 1;
      block_position[3].y = block_position[2].y;
    } break;
    case PIECE_T: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb - 1; ++i) {
        block_position[i].x += i;
      }
      // + 1 top middle
      ++block_position[3].x;
      ++block_position[3].y;
    } break;
    case PIECE_Z_RIGHT: {
      ++block_position[0].y;
      block_position[1].y = block_position[0].y;
      ++block_position[1].x;
      block_position[2].x = block_position[1].x;
      block_position[3].x = block_position[2].x + 1;
    } break;
  }
}

//MDTMP
/*
//--------------------------------------------------------------------------------
// object definition
struct TetrisPiece {
  TetrisPieceType type;
  GraphicsPoint2D position;
};

//--------------------------------------------------------------------------------
static void internal_rectangle_2D_set_context_position(
    Rectangle2D* const rectangle_2D, struct grid_position grid_position,
    const TetrisPieceType type) {
  assert(rectangle_2D);

  // initialize 4 square to init pos.
  size_t i;
  for (i = 0; i < internal_pieces_block_nb; ++i) {
    rectangle_2D[i].width = internal_block_width;
    rectangle_2D[i].height = internal_block_height;
    // MDTMP rectangle_2D[i].x = -0.6f;
    // MDTMP rectangle_2D[i].y = 0.8f - (internal_block_height * 2.0f * type);
    rectangle_2D[i].x = (float)grid_position.x * internal_block_width;
    rectangle_2D[i].y = (float)grid_position.y * internal_block_height;
  }

  switch (type) {
    case PIECE_LINE: {
      // horizontal line of 4
      for (i = 1; i < internal_pieces_block_nb; ++i) {
        rectangle_2D[i].x += ((float)i * internal_block_width);
      }
    } break;
    case PIECE_L_LEFT: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb - 1; ++i) {
        rectangle_2D[i].x += ((float)i * internal_block_width);
      }
      // + 1 top left
      rectangle_2D[3].y += internal_block_height;
    } break;
    case PIECE_L_RIGHT: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb - 1; ++i) {
        rectangle_2D[i].x += ((float)i * internal_block_width);
      }
      // + 1 top right
      rectangle_2D[3].x = rectangle_2D[2].x;
      rectangle_2D[3].y += internal_block_height;
    } break;
    case PIECE_SQUARE: {
      rectangle_2D[1].x += internal_block_width;
      rectangle_2D[2].y += internal_block_height;
      rectangle_2D[3].x += internal_block_width;
      rectangle_2D[3].y += internal_block_height;
    } break;
    case PIECE_Z_LEFT: {
      rectangle_2D[1].x += internal_block_width;
      rectangle_2D[2].x = rectangle_2D[1].x;
      rectangle_2D[2].y += internal_block_height;
      rectangle_2D[3].x = rectangle_2D[2].x + internal_block_width;
      rectangle_2D[3].y = rectangle_2D[2].y;
    } break;
    case PIECE_T: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb - 1; ++i) {
        rectangle_2D[i].x += ((float)i * internal_block_width);
      }
      // + 1 top middle
      rectangle_2D[3].x += internal_block_width;
      rectangle_2D[3].y += internal_block_height;
    } break;
    case PIECE_Z_RIGHT: {
      rectangle_2D[0].y += internal_block_height;
      rectangle_2D[1].y = rectangle_2D[0].y;
      rectangle_2D[1].x += internal_block_width;
      rectangle_2D[2].x = rectangle_2D[1].x;
      rectangle_2D[3].x = rectangle_2D[2].x + internal_block_width;
    } break;
  }
}


//--------------------------------------------------------------------------------
TetrisPiece* tetris_piece_calloc() { return calloc(1, sizeof(TetrisPiece)); }

//--------------------------------------------------------------------------------
void tetris_piece_free(TetrisPiece* tetris_piece) {
  assert(tetris_piece);
  free(tetris_piece);
}

//--------------------------------------------------------------------------------
void tetris_piece_set_type(TetrisPiece* tetris_piece, TetrisPieceType type) {
  assert(tetris_piece);
  tetris_piece->type = type;
}

//--------------------------------------------------------------------------------
void tetris_piece_set_position(TetrisPiece* tetris_piece,
                               GraphicsPoint2D position) {
  assert(tetris_piece);
  tetris_piece->position = position;
}

//--------------------------------------------------------------------------------
void tetris_piece_draw(TetrisPiece* tetris_piece[], size_t length) {
  if (!internal_bo_texture) {
    // MDTMP no uninit, memory leak...
    const char* tileset_filename = "common/assets/tmp/tetris_texture.png";
    internal_bo_texture =
        graphics_shader_texture_buffer_create(tileset_filename);
    assert(internal_bo_texture);
  }

  const size_t piece_nb = 7;
  const size_t rectangle_2D_size = piece_nb * internal_pieces_block_nb;
  Rectangle2D array_context_position[rectangle_2D_size];
  Rectangle2D array_texture_position[rectangle_2D_size];

  size_t i;
  for (i = 0; i < piece_nb; ++i) {
    // MDTMP
    // internal_rectangle_2D_set_context_position(&array_context_position[i*internal_pieces_block_nb],
    // i);
  }
  for (i = 0; i < piece_nb; ++i) {
    internal_rectangle_2D_set_texture(
        &array_texture_position[i * internal_pieces_block_nb], i);
  }

  graphics_primitive_rectangle_2D_draw(
      internal_bo_texture, array_context_position, array_texture_position,
      rectangle_2D_size);
}
*/

