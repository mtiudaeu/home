#ifndef MENU_H
#define MENU_H

namespace menu {

struct Ctx;

Ctx* create();
Ctx* destroy(Ctx* context);
void render(Ctx& context);

}

#endif

