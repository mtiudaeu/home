#include "module.h"

#include <stdio.h>

static void* init_state() {
  printf("init_state\n");
  return 0x0;
}

static void uninit_state(void*  // state
                         ) {
  printf("uninit_state\n");
}

static void load_state(void*  // state
                       ) {
  printf("load_state\n");
}

static void unload_state(void*  // state
                         ) {
  printf("unload_state\n");
}

static bool step(void*  // state
                 ) {
  printf("step\n");
  return true;
}

MODULE_EXPORT_API(init_state, uninit_state, load_state, unload_state, step);
