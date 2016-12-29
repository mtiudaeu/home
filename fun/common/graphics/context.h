#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include <stddef.h>

size_t graphics_context_global_init();
size_t graphics_context_global_uninit();

size_t graphics_context_global_run(void (*render_cb)());

#ifdef INCLUDE_RUN_TEST
size_t graphics_context_run_test();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_CONTEXT_H

