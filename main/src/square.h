#ifndef SQUARE_H
#define SQUARE_H

namespace square {
struct Ctx {
 float x;
 float y;
 float size;
//color?
};

void init();
void uninit();


//void render(Ctx& ctx);
void render();

}

#endif
