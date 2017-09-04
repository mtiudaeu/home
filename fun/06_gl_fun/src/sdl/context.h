#ifndef SDL_CONTEXT_H
#define SDL_CONTEXT_H

#include "app.h"

Status sdl_context_init();

Status sdl_context_swap_buffer();
Status sdl_context_catch_event();

#endif
