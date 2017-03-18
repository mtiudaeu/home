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

#include "log.h"
#include "module.h"

static module::library* library;

int main() {
  library = module::init(ROOT_PATH "module_manager.so");
  if (!library) {
    LOG_ERROR("!library");
    return 1;
  }

  while (module::step(*library).stepping_done != true) {
  }
  module::uninit(library);

  return 0;
}
