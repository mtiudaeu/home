#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include <SDL2/SDL.h>

#include <stddef.h>

size_t graphics_context_global_init();
size_t graphics_context_global_uninit();

// return 0 is ready
size_t graphics_context_global_ready();

size_t graphics_context_global_run(void (*main_loop_cb)(),
                                   void (*handle_hotkey_cb)(SDL_Event*));

#endif // GRAPHICS_CONTEXT_H

