#ifndef GRAPHICS_PRIMITIVE_RECTANGLE_H
#define GRAPHICS_PRIMITIVE_RECTANGLE_H

#include <GL/glew.h>

//MDTMP change to rectangle..
// MDTMP rename Rectangle2D
// MDTMP could be move out of here (reuse in physics etc..)

size_t graphics_primitive_rectangle_2D_init();
void graphics_primitive_rectangle_2D_uninit();

typedef struct Rectangle2D {
  float x; // Bottom left corner
  float y; // Bottom left corner
  float width;
  float height;
} Rectangle2D;

void graphics_primitive_rectangle_2D_draw(GLuint bo_texture,
                                       const Rectangle2D* array_context_position,
                                       const Rectangle2D* array_texture_position,
                                       size_t square_length);

#ifdef INCLUDE_RUN_TEST
size_t graphics_primitive_rectangle_2D_run_test(void (** draw_callback)(void),
                                             void (** uninit_callback)(void));

#endif  // INCLUDE_RUN_TEST

#endif  // GRAPHICS_PRIMITIVE_RECTANGLE_H