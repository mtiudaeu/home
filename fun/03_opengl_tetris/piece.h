#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

#include "common/graphics/point.h"

#include <stddef.h>

struct grid_position {
  size_t x;
  size_t y;
};

typedef enum TetrisPieceType {
  PIECE_LINE,
  PIECE_L_LEFT,
  PIECE_L_RIGHT,
  PIECE_SQUARE,
  PIECE_Z_LEFT,
  PIECE_T,
  PIECE_Z_RIGHT
} TetrisPieceType;

typedef enum TetrisPieceRotation {
  PIECE_ROT_0,
  PIECE_ROT_1,
  PIECE_ROT_2,
  PIECE_ROT_3
} TetrisPieceRotation;


typedef struct TetrisPiece TetrisPiece;

TetrisPiece* tetris_piece_calloc();
void tetris_piece_free(TetrisPiece* tetris_piece);

void tetris_piece_set_type(TetrisPiece* tetris_piece, TetrisPieceType type);
void tetris_piece_set_position(TetrisPiece* tetris_piece, GraphicsPoint2D position);

void tetris_piece_draw(TetrisPiece* tetris_piece[], size_t length);

void tetris_piece_draw_2(struct grid_position* const array_block_position,
                         TetrisPieceType* const array_block_type,
                         size_t length);

#endif // TETRIS_PIECE_H
