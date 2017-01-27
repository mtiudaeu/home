#ifndef GRAPHICS_PRIMITIVE_TRIANGLE_VERTICES_2D_H
#define GRAPHICS_PRIMITIVE_TRIANGLE_VERTICES_2D_H

//--------------------------------------------------------------------------------
typedef struct TriangleVertices2D {  // (-1.0,-1.0) is bottom left;
  GLfloat coord_1[2];
  GLfloat coord_2[2];
  GLfloat coord_3[2];
} TriangleVertices2D;

//--------------------------------------------------------------------------------
void graphics_primitive_triangle_vertices_from_square_2D(
    TriangleVertices2D triangle_vertices[2], const Square2D square_2D) {
  // FIXME Need unit test. Cannot compare float by memcmp on struct.

  const GLfloat x_left = square_2D.x - square_2D.half_width;
  const GLfloat x_right = square_2D.x + square_2D.half_width;
  const GLfloat y_bottom = square_2D.y - square_2D.half_width;
  const GLfloat y_top = square_2D.y + square_2D.half_width;

  // bottom left
  triangle_vertices[0].coord_1[0] = triangle_vertices[1].coord_1[0] = x_left;
  triangle_vertices[0].coord_1[1] = triangle_vertices[1].coord_1[1] = y_bottom;

  // top right
  triangle_vertices[0].coord_2[0] = triangle_vertices[1].coord_2[0] = x_right;
  triangle_vertices[0].coord_2[1] = triangle_vertices[1].coord_2[1] = y_top;

  // top left
  triangle_vertices[0].coord_3[0] = x_left;
  triangle_vertices[0].coord_3[1] = y_top;

  // bottom right
  triangle_vertices[1].coord_3[0] = x_right;
  triangle_vertices[1].coord_3[1] = y_bottom;
}

#endif  // GRAPHICS_PRIMITIVE_TRIANGLE_VERTICES_2D_H
