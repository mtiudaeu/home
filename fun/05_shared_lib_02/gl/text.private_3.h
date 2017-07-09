#include <string.h>

static GLuint texture_tileset = 0;

struct graphics_coord_2d {
  float x;
  float y;
};

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

//--------------------------------------------------------------------------------
// FIXME  Could accumulate all text to draw on screen and call glDrawArray once.
void graphics_text_draw(float scale,
                        struct graphics_coord_2d position, const char* msg) {
  if (!msg || !msg[0]) {
    LOG_ERROR("graphics_text_draw : invalid msg");
  }

  const size_t length_msg = strlen(msg);

  const size_t rectangle_2D_sizeof = sizeof(struct rectangle_2d) * length_msg;
  struct rectangle_2d* const array_context_position =
      (struct rectangle_2d*)malloc(rectangle_2D_sizeof);
  size_t i;
  const float width_offset = graphics_text_square_vertices_width(scale) * 0.5;
  for (i = 0; i < length_msg; ++i, position.x += width_offset) {
    graphics_text_rectangle_2D(array_context_position + i, scale,
                                    position);
  }

  struct rectangle_2d* const array_texture_position =
      (struct rectangle_2d*)malloc(rectangle_2D_sizeof);
  for (i = 0; i < length_msg; ++i) {
    graphics_text_rectangle_2D_texture(array_texture_position + i, msg[i]);
  }

  graphics_primitive_rectangle_2D_draw(texture_tileset,
                                       array_context_position,
                                       array_texture_position, length_msg);

  free(array_context_position);
  free(array_texture_position);
}


static void func3() {
  if (texture_tileset == 0) {
    // init texture
    const char* tileset_filename = "assets/tileset.png";
    texture_tileset = shader_texture_buffer_create(tileset_filename);
    // MDTMP glDeleteTextures(1, &texture_tileset);
    if (!texture_tileset) {
      LOG_ERROR("!texture_tileset");
      return;
    }

    //MDTMP this is more of an init
    const float scale = 1.0f;
    const struct graphics_coord_2d position = {0.1, 0.5};
    graphics_text_draw(scale, position, "test");
  }

}
