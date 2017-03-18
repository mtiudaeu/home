#include "module.h"

#include <stdio.h>
#include <unistd.h>

static void* init_state() {
  printf("module_manager : init_state\n");
  return 0x0;
}

static void uninit_state(void*  // state
                         ) {
  printf("module_manager : uninit_state\n");
}

static void load_state(void*  // state
                       ) {
  printf("module_manager : load_state\n");
}

static void unload_state(void*  // state
                         ) {
  printf("module_manager : unload_state\n");
}

static bool step(void*  // state
                 ) {
  printf("module_manager : step\n");
  sleep(1); 
  return true;
}

MODULE_EXPORT_API(init_state, uninit_state, load_state, unload_state, step);
