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

  size_t iteration_nb = 0;
  while (module::step(*library).stepping_done != true) {
    ++iteration_nb;
    if (iteration_nb % 2 == 0) {
      module::reload_status reload_status = module::reload_if_needed(*library);
      if (reload_status.reload_needed &&
          reload_status.reload_succeeded == false) {
        LOG_ERROR("Failed reloading module_manager");
        break;
      }
    }
  }
  module::uninit(library);

  return 0;
}
