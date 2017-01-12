#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include <SDL2/SDL.h>

#include <stddef.h>

size_t graphics_context_global_init();
size_t graphics_context_global_uninit();

// return 0 is ready
size_t graphics_context_global_ready();

//MDTMP Split with render callback and handle hotkey callback 
size_t graphics_context_global_run(void (*main_loop_cb)(SDL_Event*));

#ifdef INCLUDE_RUN_TEST
size_t graphics_context_run_test();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_CONTEXT_H

