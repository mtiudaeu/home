#include "menu.h"

#include "text.h"
#include "square.h"

namespace menu {

enum EMenu {
  Menu,
  Tetris,
  End
};

struct Ctx {
  EMenu e_menu;
  text::Context title;
  text::Context tetris;
  square::Ctx selection;
};

//--------------------------------------------------
Ctx* create() {
  Ctx* ctx = new Ctx();
  ctx->e_menu = Menu;

  ctx->title = {
.x = -8.0f,
.y = 6.0f,
.size = 1.0f,
.value = "Welcome to the menu"
};
  ctx->tetris = {
.x = -8.0f,
.y = 3.0f,
.size = 1.0f,
.value = "Tetris"
};

 ctx->selection = {
.x = -4.0f,
.y = 1.5f,
.height = 2.0f,
.width = 2.0f,
};

  return ctx;
}
//--------------------------------------------------
Ctx* destroy(Ctx* ctx) {
  
  delete ctx;
  return nullptr;
}
//--------------------------------------------------
void render(Ctx& context) {
  square::render(context.selection);
  text::render(context.title);
  text::render(context.tetris);
}


}
