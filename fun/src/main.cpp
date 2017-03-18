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
#include "log.h"


static module::library* library;
/* MDTMP
static void test_cb() {
  library.api_handle->step(library.library_state);
  sleep(1);
}
*/

int main() {
  library = module::init(ROOT_PATH"module_manager.so");
  if (!library) {
    LOG_ERROR("!library");
    return 1;
  }

  for (;;) {
//MDTMP get result
    module::step(*library);
  }
  module::uninit(library);

  return 0;
}
