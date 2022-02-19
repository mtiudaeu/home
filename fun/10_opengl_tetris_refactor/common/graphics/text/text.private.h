//--------------------------------------------------------------------------------
static float graphics_text_square_vertices_width(float scale) {
  const float size_ratio = 0.1f;
  return scale * size_ratio;
}

//--------------------------------------------------------------------------------
static void graphics_text_rectangle_2D(struct rectangle_2d* rectangle_2D, float scale,
                             struct graphics_coord_2d position) {
  assert(rectangle_2D);

  rectangle_2D->x = position.x;
  rectangle_2D->y = position.y;
  rectangle_2D->width = graphics_text_square_vertices_width(scale);
  // FIXME add height.
  rectangle_2D->height = graphics_text_square_vertices_width(scale);
}

//--------------------------------------------------------------------------------
struct grid_16x16 {  // (0,0) is top left
  unsigned int x;
  unsigned int y;
};

//--------------------------------------------------------------------------------
static struct grid_16x16 graphics_text_char_to_grid_coord(char value) {
  struct grid_16x16 coord;
  coord.x = value % 16;
  coord.y = value / 16;
  return coord;
}

//--------------------------------------------------------------------------------
#define TEXTURE_CHARACTER_WIDTH 1.0f / 16.0f
#define TEXTURE_CHARACTER_HEIGHT 1.0f / 16.0f

//--------------------------------------------------------------------------------
// rectangle_2D (0.0,0.0) is bottom left
static void graphics_text_rectangle_2D_texture(struct rectangle_2d* rectangle_2D, char value) {
  assert(rectangle_2D);

  const struct grid_16x16 character_coord = graphics_text_char_to_grid_coord(value);
  rectangle_2D->x = character_coord.x * TEXTURE_CHARACTER_WIDTH;
  rectangle_2D->y = 1.0f - (character_coord.y  * TEXTURE_CHARACTER_HEIGHT) - TEXTURE_CHARACTER_HEIGHT;
  rectangle_2D->width = TEXTURE_CHARACTER_WIDTH;
  rectangle_2D->height = TEXTURE_CHARACTER_HEIGHT;
}

