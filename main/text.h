#ifndef TEXT_H
#define TEXT_H

#include <string>

namespace text {

struct Context;

Context* create();
void render(Context& context);
Context* destroy(Context* context);

void set_value(Context& context, const std::string& value);
}

#endif

