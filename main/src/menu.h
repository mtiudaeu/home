#ifndef MENU_H
#define MENU_H

#include <SDL.h>


namespace menu {

struct Ctx;

Ctx* create();
Ctx* destroy(Ctx* ctx);
void process_event(Ctx& ctx, const SDL_Event& event);
void render(Ctx& ctx);

}

#endif

