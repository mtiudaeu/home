#include "03_opengl_tetris/piece.h"

static GLuint internal_bo_texture = 0;
//MDTMP add layout of every piece. (static)

//--------------------------------------------------------------------------------
static void internal_draw_callback() {


//--------------------------------------------------------------------------------
struct TetrisPiece {
  TetrisPieceType type;
  GraphicsPoint2D position;
};

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
void tetris_piece_draw(const TetrisPiece tetris_piece[], size_t length)
{
  if (!internal_bo_texture) {
    // MDTMP no uninit, memory leak...
    const char* tileset_filename = "common/assets/tmp/tetris_texture.png";
    internal_bo_texture = graphics_shader_texture_buffer_create(tileset_filename);
    assert(internal_bo_texture);
  }

//MDTMP make test case to map each colour square position

}
