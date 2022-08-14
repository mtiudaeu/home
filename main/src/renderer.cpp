#include <SDL.h>

#include "menu.h"
#include "square.h"
#include "text.h"

static menu::Ctx* menu_ctx;

namespace renderer {

//--------------------------------------------------
void init() {
  text::init();
  square::init();
  menu_ctx = menu::create();
}

//--------------------------------------------------
void uninit() {
  text::uninit();
  square::uninit();
  menu_ctx = menu::destroy(menu_ctx);
}

//--------------------------------------------------
void process_event(const SDL_Event& event) {
  menu::process_event(*menu_ctx, event);
}

//--------------------------------------------------
void render() { menu::render(*menu_ctx); }

}  // namespace renderer
