#include "core/status.h"
#include "core/log.h"

#include "core/module_create.h"
#include "core/module_init.h"
#include "core/data_manager.h"

static data_manager_s* data_manager = 0x0;
MODULE_DEFAULT_INIT_CB;
MODULE_DEFAULT_UNINIT_CB;

static status_s module_manager__step_cb() {
  // FIXME Doing all reloading at the same time could hit performance.
  status_s status = init_all_module(*data_manager);
  if (status.error) {
    LOG_ERROR("init_all_module");
    return status;
  }

  const size_t loop_reload_max = 10;
  size_t loop_reload_count = 0;
  for (;;) {
    ++loop_reload_count;
    // FIXME Doing all reloading at the same time could hit performance.
    if (loop_reload_count >= loop_reload_max) {
      status.error = false;
      status.info_code = STEP_INFO_NEED_RELOADING; // reload self
      return status;
    }

    for (auto module : data_manager->modules) {
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

MODULE_EXPORT(module_default_init_cb, module_default_uninit_cb, module_manager__step_cb);
