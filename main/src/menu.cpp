#include "menu.h"
#include "square.h"
#include "text.h"


namespace menu {

enum EMenu { Tetris, NextGame };

struct Ctx {
  EMenu e_menu;
  text::Context title;
  text::Context tetris;
  text::Context next_game;
  square::Ctx selection;
};

//--------------------------------------------------
Ctx* create() {
  Ctx* ctx = new Ctx();
  ctx->e_menu = Tetris;

  ctx->title = {
      .x = -8.0f, .y = 6.0f, .size = 1.0f, .value = "Welcome to the menu"};
  ctx->tetris = {.x = -8.0f, .y = 3.0f, .size = 1.0f, .value = "Tetris"};
  ctx->next_game = {.x = -8.0f, .y = 1.0f, .size = 1.0f, .value = "Next Game"};

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
void process_event(Ctx& ctx, const SDL_Event& event) {
  // mdtmp
  switch (event.type) {
    case SDL_KEYUP: {
      int sym = event.key.keysym.sym;
      if (sym == SDLK_ESCAPE) {
        //mdtmpmain_context.running = false;
      }
      if (sym == SDLK_DOWN) {
//mdtmp
       ctx.e_menu = NextGame;
      }
      if (sym == SDLK_UP) {
//mdtmp
       ctx.e_menu = Tetris;
      }
      break;
    }
  }
}

//--------------------------------------------------
void render(Ctx& ctx) {
  switch (ctx.e_menu) {
    case Tetris:
      ctx.selection.y = ctx.tetris.y / 2.0f;
      //mdtmp ctx.selection.width = 2.0f * ctx.tetris.value.size();
      //ctx.selection.width = 3.0f;
      //ctx.selection.height = 3.0f;
      break;
    case NextGame:
      ctx.selection.y = ctx.next_game.y / 2.0f;
      //mdtmp ctx.selection.width = 2.0f * ctx.next_game.value.size();
      //ctx.selection.width = 16.0f;
      break;
  }


  square::render(ctx.selection);
  text::render(ctx.title);
  text::render(ctx.tetris);
  text::render(ctx.next_game);
}

}  // namespace menu
