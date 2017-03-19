#include "module.h"

#include "log.h"

#include <unistd.h>

struct module_manager {
  module::library* context = 0x0;  // MDTMP should be an array or map of modules
};

static void* module_manager_init_state() {
  LOG_INFO("module_manager : module_manager_init_state\n");

  module::library* context = module::init(ROOT_PATH "context.so");
  if (!context) {
    return 0x0;
  }

  struct module_manager* module_manager = new struct module_manager();
  module_manager->context = context;

  return module_manager;
}

static void module_manager_uninit_state(void*  // state
                                        ) {
  LOG_INFO("module_manager : module_manager_uninit_state\n");
}

static void module_manager_load_state(void*  // state
                                      ) {
  LOG_INFO("module_manager : module_manager_load_state\n");
}

static void module_manager_unload_state(void*  // state
                                        ) {
  LOG_INFO("module_manager : module_manager_unload_state\n");
}

static bool module_manager_step(void* state) {
  LOG_INFO("module_manager : omg\n");
  if (!state) {
    LOG_ERROR("!state");
    return false;
  }
  struct module_manager* module_manager =
      static_cast<struct module_manager*>(state);
  sleep(1);  // MDTMP remove.
  return module::step(*module_manager->context).stepping_done == false;
}

MODULE_EXPORT_API(module_manager_init_state, module_manager_uninit_state,
                  module_manager_load_state, module_manager_unload_state,
                  module_manager_step);
