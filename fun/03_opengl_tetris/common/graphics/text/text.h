#ifndef GRAPHICS_TEXT_TEXT_H
#define GRAPHICS_TEXT_TEXT_H

#include "common/graphics/coord.h"

#include <stddef.h>

struct graphics_text;

struct graphics_text* graphics_text_new();
void graphics_text_delete(struct graphics_text* graphics_text);

void graphics_text_draw(const struct graphics_text* graphics_text, float scale,
                        struct graphics_coord_2d position, const char* msg);

#ifdef INCLUDE_RUN_TEST
size_t test_graphics_text_init();
size_t test_graphics_text_uninit();
void test_graphics_text_draw();

size_t test_graphics_text_run();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_TEXT_TEXT_H

