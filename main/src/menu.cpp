#include "menu.h"

#include "text.h"
#include "square.h"

namespace menu {

struct Ctx {
  EMenu e_menu;
  square::Ctx* selection;
  text::Context* title;
  text::Context* tetris;
};

//--------------------------------------------------
Ctx* create() {
  Ctx* ctx = new Ctx();
  ctx->e_menu = Menu;

  ctx->selection = square::create();
  //mdtmp set default position

  ctx->title = text::create();
  text::set_value(*ctx->title, "Welcome to the menu");
  text::set_position(*ctx->title, -8.0f, 6.0f);

  ctx->tetris = text::create();
  text::set_value(*ctx->tetris, "Tetris");
  text::set_position(*ctx->tetris, -8.0f, 3.0f);

  return ctx;
}
//--------------------------------------------------
Ctx* destroy(Ctx* ctx) {
  
  ctx->selection = square::destroy(ctx->selection);
  ctx->title = text::destroy(ctx->title);
  ctx->tetris = text::destroy(ctx->tetris);
  delete ctx;
  return nullptr;
}
//--------------------------------------------------
void render(Ctx& context) {
  text::render(*context.title);
  text::render(*context.tetris);
}

//--------------------------------------------------
EMenu get_menu(const Ctx& context) {
  return context.e_menu;
}

}
