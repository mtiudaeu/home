#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

#include <stddef.h>

//MDTMP return error?
size_t graphics_context_global_init();
size_t graphics_context_global_uninit();

void graphics_context_global_run();

#ifdef INCLUDE_RUN_TEST
size_t graphics_context_test_run();
#endif  // INCLUDE_RUN_TEST

#endif // GRAPHICS_CONTEXT_H

