#ifndef GRAPHICS_TEXT_SQUARE_VERTICES_H
#define GRAPHICS_TEXT_SQUARE_VERTICES_H

//--------------------------------------------------------------------------------
static float internal_square_vertices_width(float scale) {
  const float size_ratio = 0.1f;
  return scale * size_ratio;
}

//--------------------------------------------------------------------------------
//MDTMP add test
static void internal_text_rectangle_2D(Rectangle2D* rectangle_2D, float scale,
                             GraphicsPoint2D position) {
  assert(rectangle_2D);

  rectangle_2D->x = position.x;
  rectangle_2D->y = position.y;
  rectangle_2D->width = internal_square_vertices_width(scale);
  rectangle_2D->height = internal_square_vertices_width(scale);
}

#endif  // GRAPHICS_TEXT_SQUARE_VERTICES_H