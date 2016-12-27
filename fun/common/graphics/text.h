#ifndef GRAPHICS_TEXT_H
#define GRAPHICS_TEXT_H

#include <GL/glew.h>

typedef struct {
  GLuint texture_id;
} GraphicsText;

GraphicsText* graphics_text_from_tileset_malloc(const char* filename);
void graphics_text_free(GraphicsText* graphics_text);

//MDTMP
/*
void graphics_text_draw(GraphicsText* graphics_text);
*/

#endif // GRAPHICS_TEXT_

