#ifndef UI_TEXT_H
#define UI_TEXT_H

#include "common/graphics/point.h"

typedef struct UIText UIText;

UIText* ui_text_calloc();
void ui_text_free(UIText* ui_text);

void ui_text_set_scale(UIText* ui_text, float scale);
void ui_text_set_position(UIText* ui_text, GraphicsPoint2D position);
void ui_text_set_msg(UIText* ui_text, const char* msg);

void ui_text_draw(const UIText* ui_text);

#endif  // UI_TEXT_H
