#include "menu.h"
#include "text.h"

namespace menu {

struct Ctx {
  EMenu e_menu;
  text::Context* title;
  text::Context* tetris;
};

//--------------------------------------------------
Ctx* create() {
  Ctx* ctx = new Ctx();
  ctx->e_menu = Menu;

  ctx->title = text::create();
  text::set_value(*ctx->title, "Welcome to the menu");
  text::set_position(*ctx->title, -8.0f, 6.0f);
  ctx->tetris = text::create();
  text::set_value(*ctx->tetris, "Tetris");
  text::set_position(*ctx->tetris, -8.0f, 3.0f);

  return ctx;
}
//--------------------------------------------------
Ctx* destroy(Ctx* context) {
  context->title = text::destroy(context->title);
  context->tetris = text::destroy(context->tetris);
  delete context;
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
