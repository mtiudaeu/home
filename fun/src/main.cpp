// TODO
// Dependencies
//
// program : program_data
//           Calling state switch
//   hotkey_mouse_events <----------
//                                  |
//   state_menu : no_data           |
//      hotkey ---------------------|
//                                  |
//   state_game_loop : game_data    |
//      ai                          |
//      network                     |
//      hotkey ----------------------
//
//
//

#include "module.h"

#include "common/log/log.h"

#include <stdio.h>
#include <unistd.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

static module::library library;
static void test_cb() {
  library.api_handle->step(library.library_state);
  sleep(1);
}

int main() {
  module::load(library, "./hello.so");
  if (!library.api_handle) {
    LOG_ERROR("!library.api_handle");
    return 1;
  }

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(&test_cb,
                           0,  // fps
                           1   // simulate infinite loop
                           );
#else
  for (;;) {
    test_cb();
  }
#endif

  return 0;
}
