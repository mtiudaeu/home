#ifndef GRAPHICS_TEXT_TEXT_H
#define GRAPHICS_TEXT_TEXT_H

#include "common/graphics/coord.h"

#include <stddef.h>

typedef struct GraphicsText GraphicsText;

GraphicsText* graphics_text_calloc();
void graphics_text_free(GraphicsText* graphics_text);

void graphics_text_draw(const GraphicsText* graphics_text, float scale,
                        struct graphics_coord_2d position, const char* msg);

#ifdef INCLUDE_RUN_TEST
size_t test_graphics_text_init();
size_t test_graphics_text_uninit();
void test_graphics_text_draw();

size_t test_graphics_text_run();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_TEXT_TEXT_H

