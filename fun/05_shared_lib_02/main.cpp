#include "core/module_init.h"

#include <memory>

int module_manager_run()
{
  status_s status;

  std::unique_ptr<data_manager_s> data_manager = std::make_unique<data_manager_s>();
  std::unique_ptr<module_s> module_manager = std::make_unique<module_s>();
  module_manager->lib_path = ROOT_PATH "core_module_manager.so";

  for (;;) {
    status = init_module(*module_manager, *data_manager);
    if (status.error) {
      LOG_ERROR("init_module");
      return 1;
    }
    status = module_manager->step_cb();
    if (status.error) {
      LOG_ERROR("module_manager->step_cb");
      return 1;
    }
    else if (status.info_code == STEP_INFO_STOPPING) {
      LOG_DEBUG("status.info_code == STEP_INFO_STOPPING");
      return 0;
    }
  }

  LOG_ERROR("Should not reach here");
  return 1;
}

int main() {
  return module_manager_run();
}
