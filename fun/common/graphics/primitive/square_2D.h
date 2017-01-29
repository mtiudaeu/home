#ifndef GRAPHICS_PRIMITIVE_SQUARE_H
#define GRAPHICS_PRIMITIVE_SQUARE_H

#include <GL/glew.h>

//MDTMP change to rectangle..
// MDTMP rename Square2D
// MDTMP could be move out of here (reuse in physics etc..)

size_t graphics_primitive_square_2D_init();
void graphics_primitive_square_2D_uninit();

typedef struct Square2D {
  float x;
  float y;
  float half_width;
} Square2D;

void graphics_primitive_square_2D_draw(GLuint bo_texture,
                                       const Square2D* array_context_position,
                                       const Square2D* array_texture_position,
                                       size_t square_length);

#ifdef INCLUDE_RUN_TEST
size_t graphics_primitive_square_2D_run_test(void (** draw_callback)(void),
                                             void (** uninit_callback)(void));

#endif  // INCLUDE_RUN_TEST

#endif  // GRAPHICS_PRIMITIVE_SQUARE_H
