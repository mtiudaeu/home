#include "new_module_init.h"

int main() {
  status status;

  data_manager* data_manager = new data_manager();
  
  const size_t loop_reload_max = 10;
  size_t loop_reload_count = 0;
  for (;;) {
    // FIXME Doing all reloading at the same time could hit performance.
    if(loop_reload_count => loop_reload_max) {
      loop_reload_count = 0;
      status = init_all_module(*data_manager);
      if(status.error) {
        LOG_ERROR("init_all_module");
        return 1;
      }
    }

    for(auto module : data_manager->modules) {
      assert(module);
      if(!module->step_cb) {
        continue;
      }
      status = module->step_cb();
      if (status.error) {
        LOG_ERROR("status.error");
        return 1;
      }
      if (status.info_code == STEP_INFO_STOPPING) {
        LOG_DEBUG("status.info_code == STEP_INFO_STOPPING");
        return 0;
      }
    }
  }
}
