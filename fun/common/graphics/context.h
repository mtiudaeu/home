#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include <GL/glew.h>

typedef struct {
  GLuint program_id;
} GraphicsContext;

GraphicsContext* graphics_context_malloc();
void graphics_context_free(GraphicsContext* graphics_context);

#endif // GRAPHICS_CONTEXT_H

