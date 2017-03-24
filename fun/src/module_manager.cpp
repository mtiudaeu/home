#include "module.h"

#include "log.h"

#include <unistd.h>
#include <assert.h>

struct module_manager {
  module::library* context = 0x0;  // FIXME switch to container and manage depandancies
};

static void* module_manager_init_state(module_status& module_status) {
  LOG_DEBUG("module_manager : module_manager_init_state");

  module::library* context = module::init(ROOT_PATH "context.so", module_status);
  if (!context) {
    LOG_ERROR("module::init");
    module_status.error = true;
    return 0x0;
  }
  if (module_status.error) {
    LOG_ERROR("module::init");
    return 0x0;
  }

  struct module_manager* module_manager = new struct module_manager();
  module_manager->context = context;

  return module_manager;
}

static module_status module_manager_uninit_state(void*  // state
                                        ) {
  LOG_DEBUG("module_manager : module_manager_uninit_state");
  return module_status();
}

static module_status module_manager_load_state(void*  // state
                                      ) {
  LOG_DEBUG("module_manager : module_manager_load_state");
  return module_status();
}

static module_status module_manager_unload_state(void*  // state
                                        ) {
  LOG_DEBUG("module_manager : module_manager_unload_state");
  return module_status();
}

static module_status module_manager_step(void* state) {
  LOG_DEBUG("module_manager : step");
  assert(state);

  struct module_manager* module_manager =
      static_cast<struct module_manager*>(state);
  module_status step_status = module::step(*module_manager->context);
  if (step_status.error) {
    LOG_ERROR("step_status.error");
    return step_status;
  }
  if (step_status.info_code == module::STEP_INFO_STOPPING) {
    return step_status;
  }

  // MDTMP revisit loading strategy
  const module_status reload_status =
      module::reload_if_needed(*module_manager->context);
  if (reload_status.error) {
    LOG_ERROR("reload_if_needed");
    step_status.error = true;
    return step_status;
  }
  return step_status;
}

MODULE_EXPORT_API(module_manager_init_state, module_manager_uninit_state,
                  module_manager_load_state, module_manager_unload_state,
                  module_manager_step);
