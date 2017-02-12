#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "common/graphics/coord.h"

#include <stddef.h>

struct ui_text;

struct ui_text* ui_text_new();
void ui_text_delete(struct ui_text* ui_text);

void ui_text_set_scale(struct ui_text* ui_text, float scale);
void ui_text_set_position(struct ui_text* ui_text, struct graphics_coord_2d position);
void ui_text_set_msg(struct ui_text* ui_text, const char* msg);

void ui_text_draw(const struct ui_text* ui_text);

#ifdef INCLUDE_RUN_TEST
size_t test_ui_text_init();
size_t test_ui_text_uninit();
void test_ui_text_draw();

size_t test_ui_text_run();
#endif  // INCLUDE_RUN_TEST

#endif  // UI_TEXT_H
