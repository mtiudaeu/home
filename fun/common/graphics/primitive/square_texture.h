#ifndef GRAPHICS_PRIMITIVE_SQUARE_TEXTURE_H
#define GRAPHICS_PRIMITIVE_SQUARE_TEXTURE_H

//--------------------------------------------------------------------------------
typedef struct GridCoord16x16 {  // (0,0) is top left
  unsigned int x;
  unsigned int y;
} GridCoord16x16;

//--------------------------------------------------------------------------------
static GridCoord16x16 internal_char_to_grid_coord(char value) {
  GridCoord16x16 coord;
  coord.x = value % 16;
  coord.y = value / 16;
  return coord;
}

//--------------------------------------------------------------------------------
#define TEXTURE_CHARACTER_WIDTH 1.0f / 16.0f
typedef struct SquareTexture {  // (0.0,0.0) is bottom left;
  GLfloat bottom_left_1[2];
  GLfloat top_right_1[2];
  GLfloat top_left_1[2];
  GLfloat bottom_left_2[2];
  GLfloat top_right_2[2];
  GLfloat bottom_right_2[2];
} SquareTexture;

//--------------------------------------------------------------------------------
static void internal_square_texture_fill(SquareTexture* square_texture,
                                         GridCoord16x16 coord) {
  assert(square_texture);

  const GLfloat x_left = (float)coord.x * TEXTURE_CHARACTER_WIDTH;
  const GLfloat x_right = x_left + TEXTURE_CHARACTER_WIDTH;
  const GLfloat y_top = 1.0f - (coord.y * TEXTURE_CHARACTER_WIDTH);
  const GLfloat y_bottom = y_top - TEXTURE_CHARACTER_WIDTH;

  square_texture->bottom_left_1[0] = square_texture->bottom_left_2[0] = x_left;
  square_texture->bottom_left_1[1] = square_texture->bottom_left_2[1] =
      y_bottom;

  square_texture->top_right_1[0] = square_texture->top_right_2[0] = x_right;
  square_texture->top_right_1[1] = square_texture->top_right_2[1] = y_top;

  square_texture->top_left_1[0] = x_left;
  square_texture->top_left_1[1] = y_top;

  square_texture->bottom_right_2[0] = x_right;
  square_texture->bottom_right_2[1] = y_bottom;
}

//--------------------------------------------------------------------------------
static void internal_square_texture_set_value(SquareTexture* square_texture,
                                              char value) {
  // FIXME Need more unit test. Cannot compare float by memcmp on struct.
  assert(square_texture);
  GridCoord16x16 character_coord = internal_char_to_grid_coord(value);
  internal_square_texture_fill(square_texture, character_coord);
}

#endif  // GRAPHICS_PRIMITIVE_SQUARE_TEXTURE_H
