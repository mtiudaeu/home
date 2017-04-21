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

#include "core/log.h"
#include "core/module.h"

static module::library* library;

int main() {
  {
    module_status module_status;
    library = module::init(ROOT_PATH "main_lib.so", module_status);
    if (!library) {
      LOG_ERROR("!library");
      return 1;
    }
    if (module_status.error) {
      LOG_ERROR("module_status.error");
      return 1;
    }
  }

  //MDTMP revisite reloading strategy
  module_status reload_status;
  module_status step_status;
  for (;;) {
    reload_status = module::reload_if_needed(*library);
    if (reload_status.error) {
      LOG_ERROR("module::reload_if_needed");
      break;
    }

    step_status = module::step(*library);
    if (step_status.error) {
      LOG_ERROR("step_status.error");
      break;
    }
    if (step_status.info_code == module::STEP_INFO_STOPPING) {
      LOG_DEBUG("step_status.info_code == module::STEP_INFO_STOPPING");
      break;
    }
  }

  if (module::uninit(library).error) {
    LOG_ERROR("module::uninit");
    return 1;
  }

  return step_status.error || reload_status.error;
}
