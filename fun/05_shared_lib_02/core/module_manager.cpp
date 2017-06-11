#include "core/log.h"
#include "core/module_init.h"

MODULE_DEFAULT_INITIALIZE;

namespace {
const char* dso_array[] = {ROOT_PATH "game_context.so",
                           ROOT_PATH "game_catch_event.so",
                           ROOT_PATH "game_update.so",
                           ROOT_PATH "game_render.so"};

}

static status_s module_manager_step_cb() {
  module_data_s* module_data = static_cast<module_data_s*>(
    data_manager->get_data(DSI_MODULES));
  assert(module_data);
  if(module_data->modules.empty()) { // add modules in data_manager
    const size_t lib_array_size = sizeof(dso_array) / sizeof(dso_array[0]);
    for (size_t i = 0; i < lib_array_size; ++i) {
      std::unique_ptr<module_s> module = std::make_unique<module_s>();
      module->lib_path = dso_array[i];
      module_data->modules.push_back(std::move(module));
    }
  }

  // FIXME Doing all reloading at the same time could hit performance.
  status_s status = init_all_module(*data_manager); // load/reload all modules
  if (status.error) {
    LOG_ERROR("init_all_module");
    return status;
  }

  const size_t loop_reload_max = 10;
  size_t loop_reload_count = 0;
  for (;;) {
    ++loop_reload_count;
    if (loop_reload_count >= loop_reload_max) {
      return status; // exit function to allow reloading self
    }

    for (const auto& module : module_data->modules) {
      assert(module);
      if (!module->step_cb) {
        continue;
      }
      status = module->step_cb();
      if (status.error) {
        LOG_ERROR("status.error");
        return status;
      }
      if (status.info_code == STEP_INFO_STOPPING) {
        LOG_DEBUG("status.info_code == STEP_INFO_STOPPING");
        return status;
      }
    }
  }
  return status;
}

MODULE_EXPORT_STEP_CB(module_manager_step_cb);
