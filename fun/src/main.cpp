// TODO
// Dependencies
//
// program : program_data
//           Calling state switch
//   hotkey_mouse_events <----------
//                                  \
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

#include <unistd.h>
#include <stdio.h>

int main() {
  module::library library;
  module::load(library, "./hello.so");
  if (!library.api_handle) {
    LOG_ERROR("!library.api_handle");
    return 1;
  }

  for (;;) {
    library.api_handle->step(library.library_state);
    sleep(1);
  }
  return 0;
}
