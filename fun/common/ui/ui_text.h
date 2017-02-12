#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "common/graphics/coord.h"

#include <stddef.h>

typedef struct UIText UIText;

UIText* ui_text_calloc();
void ui_text_free(UIText* ui_text);

void ui_text_set_scale(UIText* ui_text, float scale);
void ui_text_set_position(UIText* ui_text, struct graphics_coord_2d position);
void ui_text_set_msg(UIText* ui_text, const char* msg);

void ui_text_draw(const UIText* ui_text);

#ifdef INCLUDE_RUN_TEST
size_t test_ui_text_init();
size_t test_ui_text_uninit();
void test_ui_text_draw();

size_t test_ui_text_run();
#endif  // INCLUDE_RUN_TEST

#endif  // UI_TEXT_H
