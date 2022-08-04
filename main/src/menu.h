#ifndef MENU_H
#define MENU_H

enum EMenu {
  Menu,
  Tetris,
  End
};

namespace menu {

struct Ctx;

Ctx* create();
Ctx* destroy(Ctx* context);
void render(Ctx& context);

EMenu get_menu(const Ctx& context);
}

#endif

