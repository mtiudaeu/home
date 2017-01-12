#ifndef GRAPHICS_TEXT_SQUARE_VERTICES_H
#define GRAPHICS_TEXT_SQUARE_VERTICES_H

//--------------------------------------------------------------------------------
static float internal_square_vertices_half_width(float scale) {
  // FIXME_2 change scale to enum of specific text related type
  // FIXME_2 harcoded size ratio
  const float size_ratio = 0.1f;
  return scale * size_ratio;
}

//--------------------------------------------------------------------------------
typedef struct SquareVertices {  // (-1.0,-1.0) is bottom left;
  GLfloat bottom_left_1[2];
  GLfloat top_right_1[2];
  GLfloat top_left_1[2];
  GLfloat bottom_left_2[2];
  GLfloat top_right_2[2];
  GLfloat bottom_right_2[2];
} SquareVertices;

//--------------------------------------------------------------------------------
void internal_square_vertices_set_value(SquareVertices* square_vertices,
                                        float scale, GraphicsPoint2D position) {
  // FIXME Need unit test. Cannot compare float by memcmp on struct.
  assert(square_vertices);

  const float size_ratio = 0.1f;
  const float half_size_square = internal_square_vertices_half_width(scale);

  const GLfloat x_left = position.x - half_size_square;
  const GLfloat x_right = position.x + half_size_square;
  const GLfloat y_top = position.y + half_size_square;
  const GLfloat y_bottom = position.y - half_size_square;

  square_vertices->bottom_left_1[0] = square_vertices->bottom_left_2[0] =
      x_left;
  square_vertices->bottom_left_1[1] = square_vertices->bottom_left_2[1] =
      y_bottom;

  square_vertices->top_right_1[0] = square_vertices->top_right_2[0] = x_right;
  square_vertices->top_right_1[1] = square_vertices->top_right_2[1] = y_top;

  square_vertices->top_left_1[0] = x_left;
  square_vertices->top_left_1[1] = y_top;

  square_vertices->bottom_right_2[0] = x_right;
  square_vertices->bottom_right_2[1] = y_bottom;
}

#endif  // GRAPHICS_TEXT_SQUARE_VERTICES_H
