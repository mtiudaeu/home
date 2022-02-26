#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "math/vec.h"

#include <stddef.h>

struct graphics_ui_text;

struct graphics_ui_text* graphics_ui_text_new();
void graphics_ui_text_delete(struct graphics_ui_text* graphics_ui_text);

void graphics_ui_text_set_scale(struct graphics_ui_text* graphics_ui_text, float scale);
void graphics_ui_text_set_position(struct graphics_ui_text* graphics_ui_text, struct math_vec2 position);
void graphics_ui_text_set_msg(struct graphics_ui_text* graphics_ui_text, const char* msg);

void graphics_ui_text_draw(const struct graphics_ui_text* graphics_ui_text);

#endif  // UI_TEXT_H
