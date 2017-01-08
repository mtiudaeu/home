#ifndef GRAPHICS_TEXT_H
#define GRAPHICS_TEXT_H

#include "graphics/point.h"

#include <stddef.h>

typedef struct GraphicsText GraphicsText;

GraphicsText* graphics_text_from_tileset_calloc(const char* filename);
void graphics_text_free(GraphicsText* graphics_text);

void graphics_text_draw(GraphicsText* graphics_text, float scale,
                        GraphicsPoint2D position, const char* msg);

#ifdef INCLUDE_RUN_TEST
size_t graphics_text_run_test();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_TEXT_H

