#include "menu.h"

#include "text.h"
//#include "square.h"

namespace menu {

enum EMenu {
  Menu,
  Tetris,
  End
};

struct Ctx {
  EMenu e_menu;
  //square::Ctx* selection;
  text::Context title;
  text::Context tetris;
};

//--------------------------------------------------
Ctx* create() {
  Ctx* ctx = new Ctx();
  ctx->e_menu = Menu;

  //ctx->selection = square::create();
  //mdtmp set default position

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

  return ctx;
}
//--------------------------------------------------
Ctx* destroy(Ctx* ctx) {
  
  //ctx->selection = square::destroy(ctx->selection);
  delete ctx;
  return nullptr;
}
//--------------------------------------------------
void render(Ctx& context) {
  text::render(context.title);
  text::render(context.tetris);
}


}
