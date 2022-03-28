#ifndef GRAPHIC_CONTEXT_H
#define GRAPHIC_CONTEXT_H

#include <SDL2/SDL.h>

#include <stddef.h>

size_t graphic_context_global_init();
size_t graphic_context_global_uninit();

size_t graphic_context_global_run(void (*main_loop_cb)(float),
                                   void (*handle_hotkey_cb)(SDL_Event*));

#endif

