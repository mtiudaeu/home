#ifndef SQUARE_H
#define SQUARE_H

namespace square {
struct Ctx;

Ctx* create();
Ctx* destroy(Ctx* ctx);

void render(Ctx& ctx);

}

#endif
