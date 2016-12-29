#ifndef GRAPHICS_TEXT_H
#define GRAPHICS_TEXT_H

#include <GL/glew.h>

typedef struct {
  GLuint texture_id;
  GLuint program_id;
  GLuint vbo_triangle;
  GLuint vbo_texture;
  GLuint uniform_mytexture;
  GLint attribute_coord2d;
  GLint attribute_texcoord;
} GraphicsText;

GraphicsText* graphics_text_from_tileset_malloc(const char* filename);
void graphics_text_free(GraphicsText* graphics_text);

void graphics_text_draw(GraphicsText* graphics_text);

#ifdef INCLUDE_RUN_TEST
size_t graphics_text_run_test();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_TEXT_

