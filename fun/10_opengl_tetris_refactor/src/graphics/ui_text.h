#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "graphics/coord.h"

#include <stddef.h>

struct graphics_ui_text;

struct graphics_ui_text* graphics_ui_text_new();
void graphics_ui_text_delete(struct graphics_ui_text* graphics_ui_text);

void graphics_ui_text_set_scale(struct graphics_ui_text* graphics_ui_text, float scale);
void graphics_ui_text_set_position(struct graphics_ui_text* graphics_ui_text, struct graphics_coord_2d position);
void graphics_ui_text_set_msg(struct graphics_ui_text* graphics_ui_text, const char* msg);

void graphics_ui_text_draw(const struct graphics_ui_text* graphics_ui_text);

#ifdef INCLUDE_RUN_TEST
size_t test_graphics_ui_text_init();
size_t test_graphics_ui_text_uninit();
void test_graphics_ui_text_draw();

size_t test_graphics_ui_text_run();
#endif  // INCLUDE_RUN_TEST

#endif  // UI_TEXT_H
