#ifndef GRAPHICS_TEXT_TEXT_H
#define GRAPHICS_TEXT_TEXT_H

#include "math/vec.h"

#include <stddef.h>

struct graphics_text;

struct graphics_text* graphics_text_new();
void graphics_text_delete(struct graphics_text* graphics_text);

void graphics_text_draw(const struct graphics_text* graphics_text, float scale,
                        struct math_vec2 position, const char* msg);

#endif // GRAPHICS_TEXT_TEXT_H

