#ifndef TEXT_H
#define TEXT_H

namespace text {

struct Context;

Context* create();
void render(Context& context);
Context* destroy(Context* context);

}

#endif

