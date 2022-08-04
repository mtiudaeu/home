#include "menu.h"

static menu::Ctx* menu_ctx;

namespace renderer {

//--------------------------------------------------
void init() {
menu_ctx = menu::create();
}

//--------------------------------------------------
void uninit() {
menu_ctx = menu::destroy(menu_ctx);
}

//--------------------------------------------------
void render() {
menu::render(*menu_ctx);
}

}
