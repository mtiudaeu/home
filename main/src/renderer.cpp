#include "text.h"
#include "square.h"
#include "menu.h"

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
void render() {
menu::render(*menu_ctx);
}

}
