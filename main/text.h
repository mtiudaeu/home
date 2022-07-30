#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace text {

struct Context;

Context* create();
Context* destroy(Context* context);

void render(Context& context);
void set_value(Context& context, const std::string& value);
void set_position(Context& context, float x, float y);
void set_size(Context& context, float size);
}

#endif

