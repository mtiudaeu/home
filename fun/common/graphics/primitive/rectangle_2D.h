#ifndef GRAPHICS_PRIMITIVE_RECTANGLE_H
#define GRAPHICS_PRIMITIVE_RECTANGLE_H

#include <GL/glew.h>

struct rectangle_2d {
  float x; // Bottom left corner
  float y; // Bottom left corner
  float width;
  float height;
};

size_t graphics_primitive_rectangle_2D_init();
void graphics_primitive_rectangle_2D_uninit();

void graphics_primitive_rectangle_2D_draw(GLuint bo_texture,
                                       const struct rectangle_2d* array_context_position,
                                       const struct rectangle_2d* array_texture_position,
                                       size_t square_length);

#ifdef INCLUDE_RUN_TEST
size_t test_graphics_primitive_rectangle_2D_init();
size_t test_graphics_primitive_rectangle_2D_uninit();
void test_graphics_primitive_rectangle_2D_draw();

size_t test_graphics_primitive_rectangle_2D_run();

#endif  // INCLUDE_RUN_TEST

#endif  // GRAPHICS_PRIMITIVE_RECTANGLE_H
