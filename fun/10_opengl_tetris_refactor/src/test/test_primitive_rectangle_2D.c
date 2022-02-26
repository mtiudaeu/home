#include "test/test_primitive_rectangle_2D.h"

#include "graphics/primitive_rectangle_2D.h"
#include "graphics/shader.h"

#include <assert.h>

static GLuint graphics_primitive_rectangle_2Dbo_texture = 0;

//--------------------------------------------------------------------------------
size_t test_graphics_primitive_rectangle_2D_init() {
  assert(graphics_primitive_rectangle_2D_init() == 0);
  const char* tileset_filename = "ressources/tetris/tetris.png";
  graphics_primitive_rectangle_2Dbo_texture =
      graphics_shader_texture_buffer_create(tileset_filename);
  assert(graphics_primitive_rectangle_2Dbo_texture);

  return 0;
}

//--------------------------------------------------------------------------------
size_t test_graphics_primitive_rectangle_2D_uninit() {
  glDeleteTextures(1, &graphics_primitive_rectangle_2Dbo_texture);
  graphics_primitive_rectangle_2D_uninit();

  return 0;
}

//--------------------------------------------------------------------------------
void test_graphics_primitive_rectangle_2D_draw() {
  struct rectangle_2d rectangle_2D;
  rectangle_2D.x = -0.2f;
  rectangle_2D.y = -0.2f;
  rectangle_2D.width = 0.2f;
  rectangle_2D.height = 0.2f;

  struct rectangle_2d array_context_position[2];
  array_context_position[0] = rectangle_2D;
  rectangle_2D.y = 0.6f;
  array_context_position[1] = rectangle_2D;

  float texture_increment_x = 1.0f / 5.0f;
  float texture_increment_y = 1.0f / 2.0f;
  rectangle_2D.width = texture_increment_x;
  rectangle_2D.height = texture_increment_y;
  rectangle_2D.x = (1.0f * texture_increment_x);
  rectangle_2D.y = (3.0f * texture_increment_y);

  struct rectangle_2d array_texture_position[2];
  array_texture_position[0] = rectangle_2D;
  array_texture_position[1] = rectangle_2D;

  graphics_primitive_rectangle_2D_draw(
      graphics_primitive_rectangle_2Dbo_texture, array_context_position,
      array_texture_position, 2);
}

//--------------------------------------------------------------------------------
size_t test_graphics_primitive_rectangle_2D_run() {
  return 0;
}
