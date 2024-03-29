#include "graphics/primitive_text.h"

#include "graphics/context.h"
#include "math/vec.h"

#include "graphics/shader.h"

#include "common/test.h"

#include "common/log.h"

#include <GL/glew.h>

#include <stdlib.h>
#include <string.h>

#include "graphics/primitive_text.private.h"

//--------------------------------------------------------------------------------
struct graphics_text {
  GLuint tbo_texture_tileset;
};

//--------------------------------------------------------------------------------
struct graphics_text* graphics_text_new() {
  struct graphics_text* graphics_text = calloc(1, sizeof(struct graphics_text));

  {  // Create texture map objects
    const char* tileset_filename = "ressources/text/tileset.png";
    graphics_text->tbo_texture_tileset =
        graphics_shader_texture_buffer_create(tileset_filename);
    if (!graphics_text->tbo_texture_tileset) {
      LOG_ERROR("!graphics_text->tbo_texture_tileset");
      graphics_text_delete(graphics_text);
      return 0x0;
    }
  }

  return graphics_text;
}

//--------------------------------------------------------------------------------
void graphics_text_delete(struct graphics_text* graphics_text) {
  assert(graphics_text);

  glDeleteTextures(1, &graphics_text->tbo_texture_tileset);

  free(graphics_text);
}

//--------------------------------------------------------------------------------
// FIXME  Could accumulate all text to draw on screen and call glDrawArray once.
void graphics_text_draw(const struct graphics_text* graphics_text, float scale,
                        struct math_vec2 position, const char* msg) {
  assert(graphics_text);
  if (!msg || !msg[0]) {
    LOG_ERROR("graphics_text_draw : invalid msg");
  }

  const size_t length_msg = strlen(msg);

  const size_t rectangle_2D_sizeof = sizeof(struct rectangle_2d) * length_msg;
  struct rectangle_2d* const array_context_position =
      (struct rectangle_2d*)malloc(rectangle_2D_sizeof);
  size_t i;
  const float width_offset = _graphics_text_square_vertices_width(scale) * 0.5;
  for (i = 0; i < length_msg; ++i, position.x += width_offset) {
    _graphics_text_rectangle_2D(array_context_position + i, scale,
                                    position);
  }

  struct rectangle_2d* const array_texture_position =
      (struct rectangle_2d*)malloc(rectangle_2D_sizeof);
  for (i = 0; i < length_msg; ++i) {
    _graphics_text_rectangle_2D_texture(array_texture_position + i, msg[i]);
  }

  graphics_primitive_rectangle_2D_draw(graphics_text->tbo_texture_tileset,
                                       array_context_position,
                                       array_texture_position, length_msg);

  free(array_context_position);
  free(array_texture_position);
}
