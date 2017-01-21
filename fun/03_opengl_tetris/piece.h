#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

typedef struct TetrisPiece TetrisPiece;

TetrisPiece* tetris_piece_calloc();
void tetris_piece_free(TetrisPiece* tetris_piece);

void tetris_piece_draw(const TetrisPiece* tetris_piece,
                       GraphicsPoint2D position);
#endif // TETRIS_PIECE_H
