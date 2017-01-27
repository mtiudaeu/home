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
//MDTMP add test
static void internal_text_square_2D(Square2D* square_2D, float scale,
                             GraphicsPoint2D position) {
  assert(square_2D);

  square_2D->x = position.x;
  square_2D->y = position.y;
  square_2D->half_width = internal_square_vertices_half_width(scale);
}

#endif  // GRAPHICS_TEXT_SQUARE_VERTICES_H
