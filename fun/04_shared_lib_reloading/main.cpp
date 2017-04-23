#include "core/log.h"
#include "core/module.h"

static module::library* main_library;

int main() {
  { // init main lib
    module_status module_status;
    main_library = module::init(ROOT_PATH "main_lib.so", module_status);
    if (!main_library) {
      LOG_ERROR("!main_library");
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
  for (;;) { // main loop
    reload_status = module::reload_if_needed(*main_library);
    if (reload_status.error) {
      LOG_ERROR("module::reload_if_needed");
      break;
    }

    step_status = module::step(*main_library);
    if (step_status.error) {
      LOG_ERROR("step_status.error");
      break;
    }
    if (step_status.info_code == module::STEP_INFO_STOPPING) {
      LOG_DEBUG("step_status.info_code == module::STEP_INFO_STOPPING");
      break;
    }
  }

  if (module::uninit(main_library).error) {
    LOG_ERROR("module::uninit");
    return 1;
  }

  return step_status.error || reload_status.error;
}
