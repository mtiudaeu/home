//--------------------------------------------------------------------------------
struct triangle_verticles_2d {  // (-1.0,-1.0) is bottom left;
  GLfloat coord_1[2];
  GLfloat coord_2[2];
  GLfloat coord_3[2];
};

//--------------------------------------------------------------------------------
void graphics_primitive_triangle_vertices_from_rectangle_2D(
    struct triangle_verticles_2d triangle_vertices[2], const struct rectangle_2d rectangle_2D) {
  const GLfloat x_left = rectangle_2D.x;
  const GLfloat x_right = rectangle_2D.x + rectangle_2D.width;
  const GLfloat y_bottom = rectangle_2D.y;
  const GLfloat y_top = rectangle_2D.y + rectangle_2D.height;

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
