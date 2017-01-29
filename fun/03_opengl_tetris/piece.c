#include "03_opengl_tetris/piece.h"

#include "common/graphics/primitive/rectangle_2D.h"

#include "common/graphics/shader.h"

#include <stdlib.h>
#include <assert.h>

static GLuint internal_bo_texture = 0;
//MDTMP add layout of every piece. (static)

//--------------------------------------------------------------------------------
struct TetrisPiece {
  TetrisPieceType type;
  GraphicsPoint2D position;
}; 

//--------------------------------------------------------------------------------
void internal_rectangle_2D_set_context_position(Rectangle2D* rectangle_2D,
                                                const TetrisPieceType type) {
  assert(rectangle_2D);

  rectangle_2D->x = -0.8f;
  rectangle_2D->y = 0.8f - (0.2f*type);
  rectangle_2D->width = 0.2f;
  rectangle_2D->height = 0.2f;
}
//--------------------------------------------------------------------------------
void internal_rectangle_2D_set_texture(Rectangle2D* rectangle_2D,
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
  Rectangle2D array_context_position[piece_nb];
  Rectangle2D array_texture_position[piece_nb];

  size_t i;
  for (i = 0; i < piece_nb; ++i) {
    internal_rectangle_2D_set_context_position(&array_context_position[i], i);
  }
  for (i = 0; i < piece_nb; ++i) {
    internal_rectangle_2D_set_texture(&array_texture_position[i], i);
  }

  graphics_primitive_rectangle_2D_draw(internal_bo_texture, array_context_position,
                                    array_texture_position, piece_nb);
}

