#ifndef GRAPHICS_TEXT_SQUARE_TEXTURE_H
#define GRAPHICS_TEXT_SQUARE_TEXTURE_H

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
#define TEXTURE_CHARACTER_HALF_WIDTH (TEXTURE_CHARACTER_WIDTH / 2.0f);

//--------------------------------------------------------------------------------
// rectangle_2D (0.0,0.0) is bottom left
//MDTMP add test
static void internal_text_rectangle_2D_texture(Rectangle2D* rectangle_2D, char value) {
  assert(rectangle_2D);

  const GridCoord16x16 character_coord = internal_char_to_grid_coord(value);
  rectangle_2D->x = character_coord.x * TEXTURE_CHARACTER_WIDTH + TEXTURE_CHARACTER_HALF_WIDTH;
  rectangle_2D->y = 1.0f - (character_coord.y  * TEXTURE_CHARACTER_WIDTH) - TEXTURE_CHARACTER_HALF_WIDTH;
  rectangle_2D->half_width = TEXTURE_CHARACTER_HALF_WIDTH;
}

#endif  // GRAPHICS_TEXT_SQUARE_TEXTURE_H
