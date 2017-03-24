#include "module.h"

#include "log.h"

#include <vector>
#include <memory>

#include <unistd.h>
#include <assert.h>

struct module_manager {
  std::vector<module::library*> libraries;
};

static void* module_manager_init_state(module_status& module_status) {
  LOG_DEBUG("module_manager : module_manager_init_state");
  std::unique_ptr<module_manager> module_manager_guard_ptr = std::make_unique<module_manager>();

  { //catch_event
    module::library* library = module::init(ROOT_PATH "catch_event.so", module_status);
    if (!library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    module_manager_guard_ptr->libraries.push_back(library);
  }
  { //render
    module::library* library = module::init(ROOT_PATH "render.so", module_status);
    if (!library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    module_manager_guard_ptr->libraries.push_back(library);
  }
  { //context
    module::library* library = module::init(ROOT_PATH "context.so", module_status);
    if (!library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    module_manager_guard_ptr->libraries.push_back(library);
  }

  return module_manager_guard_ptr.release();
}

static module_status module_manager_step(void* state) {
  LOG_DEBUG("module_manager : step");
  assert(state);
  struct module_manager* module_manager =
      static_cast<struct module_manager*>(state);

  for (module::library* library : module_manager->libraries) {
    assert(library);

    module_status step_status = module::step(*library);
    if (step_status.error) {
      LOG_ERROR("step_status.error");
      return step_status;
    }
    if (step_status.info_code == module::STEP_INFO_STOPPING) {
      return step_status;
    }

    // MDTMP revisit loading strategy
    const module_status reload_status =
        module::reload_if_needed(*library);
    if (reload_status.error) {
      LOG_ERROR("reload_if_needed");
      step_status.error = true;
      return step_status;
    }
  }
  return module_status();
}

MODULE_EXPORT_API(module_manager_init_state, 0x0,
                  0x0, 0x0,
                  module_manager_step);
