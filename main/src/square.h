#ifndef SQUARE_H
#define SQUARE_H

namespace square {
struct Ctx {
 float x;
 float y;
 float height;
 float width;
//color?
};

void init();
void uninit();


void render(Ctx& ctx);

}

#endif
