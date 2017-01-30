#include "03_opengl_tetris/piece.h"

#include "common/graphics/primitive/rectangle_2D.h"

#include "common/graphics/shader.h"

#include <stdlib.h>
#include <assert.h>

static const size_t internal_pieces_block_nb = 4;

static GLuint internal_bo_texture = 0;

//--------------------------------------------------------------------------------
struct TetrisPiece {
  TetrisPieceType type;
  GraphicsPoint2D position;
}; 

//--------------------------------------------------------------------------------
void internal_rectangle_2D_set_context_position(Rectangle2D* const rectangle_2D,
                                                const TetrisPieceType type) {
  assert(rectangle_2D);

  // initialize 4 square to init pos.
  size_t i;
  for (i = 0; i < internal_pieces_block_nb; ++i) {
    rectangle_2D[i].width = 0.1f;
    rectangle_2D[i].height = 0.1f;
    rectangle_2D[i].x = -0.6f;
    rectangle_2D[i].y = 0.8f - (rectangle_2D[i].height * 2.0f * type);
  }

  switch (type) {
    case PIECE_LINE: {
      // horizontal line of 4
      for (i = 1; i < internal_pieces_block_nb; ++i) {
        rectangle_2D[i].x += ((float)i * rectangle_2D->width);
      }
    } break;
    case PIECE_L_LEFT: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb-1; ++i) {
        rectangle_2D[i].x += ((float)i * rectangle_2D->width);
      }
      // + 1 top left
      rectangle_2D[3].y += rectangle_2D->height;
    } break;
    case PIECE_L_RIGHT: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb-1; ++i) {
        rectangle_2D[i].x += ((float)i * rectangle_2D->width);
      }
      // + 1 top right
      rectangle_2D[3].x = rectangle_2D[2].x;
      rectangle_2D[3].y += rectangle_2D->height;
    } break;
    case PIECE_SQUARE: {
      rectangle_2D[1].x += rectangle_2D[1].width;
      rectangle_2D[2].y += rectangle_2D[2].height;
      rectangle_2D[3].x += rectangle_2D[1].width;
      rectangle_2D[3].y += rectangle_2D[2].height;
    } break;
    case PIECE_Z_LEFT: {
      rectangle_2D[1].x += rectangle_2D[1].width;
      rectangle_2D[2].x = rectangle_2D[1].x;
      rectangle_2D[2].y += rectangle_2D[2].height;
      rectangle_2D[3].x = rectangle_2D[2].x + rectangle_2D[3].width;
      rectangle_2D[3].y = rectangle_2D[2].y;
    } break;
    case PIECE_T: {
      // horizontal line of 3
      for (i = 1; i < internal_pieces_block_nb-1; ++i) {
        rectangle_2D[i].x += ((float)i * rectangle_2D->width);
      }
      // + 1 top middle
      rectangle_2D[3].x += rectangle_2D->width;
      rectangle_2D[3].y += rectangle_2D->height;
    } break;
    case PIECE_Z_RIGHT: {
      rectangle_2D[0].y += rectangle_2D[0].height;
      rectangle_2D[1].y = rectangle_2D[0].y;
      rectangle_2D[1].x += rectangle_2D[1].width;
      rectangle_2D[2].x = rectangle_2D[1].x;
      rectangle_2D[3].x = rectangle_2D[2].x + rectangle_2D[3].width;
    } break;
  }
}

//--------------------------------------------------------------------------------
void internal_rectangle_2D_set_texture(Rectangle2D* const rectangle_2D,
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

  size_t i;
  for (i = 1; i < internal_pieces_block_nb; ++i) {
    rectangle_2D[i].width = rectangle_2D->width;
    rectangle_2D[i].height = rectangle_2D->height;
    rectangle_2D[i].x = rectangle_2D->x;
    rectangle_2D[i].y = rectangle_2D->y;
  }
}

//--------------------------------------------------------------------------------
TetrisPiece* tetris_piece_calloc()
{
  return calloc(1, sizeof(TetrisPiece));
}

//--------------------------------------------------------------------------------
void tetris_piece_free(TetrisPiece* tetris_piece)
{
  assert(tetris_piece);
  free(tetris_piece);
}

//--------------------------------------------------------------------------------
void tetris_piece_set_type(TetrisPiece* tetris_piece, TetrisPieceType type)
{
  assert(tetris_piece);
  tetris_piece->type = type;
}

//--------------------------------------------------------------------------------
void tetris_piece_set_position(TetrisPiece* tetris_piece, GraphicsPoint2D position)
{
  assert(tetris_piece);
  tetris_piece->position = position;
}

//--------------------------------------------------------------------------------
void tetris_piece_draw(TetrisPiece* tetris_piece[], size_t length)
{
  if (!internal_bo_texture) {
    // MDTMP no uninit, memory leak...
    const char* tileset_filename = "common/assets/tmp/tetris_texture.png";
    internal_bo_texture = graphics_shader_texture_buffer_create(tileset_filename);
    assert(internal_bo_texture);
  }

  const size_t piece_nb = 7;
  const size_t rectangle_2D_size = piece_nb*internal_pieces_block_nb;
  Rectangle2D array_context_position[rectangle_2D_size];
  Rectangle2D array_texture_position[rectangle_2D_size];

  size_t i;
  for (i = 0; i < piece_nb; ++i) {
    internal_rectangle_2D_set_context_position(&array_context_position[i*internal_pieces_block_nb], i);
  }
  for (i = 0; i < piece_nb; ++i) {
    internal_rectangle_2D_set_texture(&array_texture_position[i*internal_pieces_block_nb], i);
  }

  graphics_primitive_rectangle_2D_draw(internal_bo_texture, array_context_position,
                                    array_texture_position, rectangle_2D_size);
}

