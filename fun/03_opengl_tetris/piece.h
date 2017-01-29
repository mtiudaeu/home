#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include "common/graphics/point.h"

enum TetrisPieceType {
  PIECE_LINE,
  PIECE_L_LEFT,
  PIECE_L_RIGHT,
  PIECE_SQUARE,
  PIECE_Z_LEFT,
  PIECE_T,
  PIECE_Z_RIGHT
};

typedef struct TetrisPiece TetrisPiece;

TetrisPiece* tetris_piece_calloc();
void tetris_piece_free(TetrisPiece* tetris_piece);

void tetris_piece_set_type(TetrisPiece* tetris_piece, TetrisPieceType type);
void tetris_piece_set_position(TetrisPiece* tetris_piece, GraphicsPoint2D position);

void tetris_piece_draw(const TetrisPiece tetris_piece[], size_t length);

#endif // TETRIS_PIECE_H
