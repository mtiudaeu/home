#include "core/log.h"
#include "core/module.h"

#include <vector>
#include <memory>

#include <unistd.h>
#include <assert.h>

struct main_lib {
  std::vector<module::library*> libraries;
};

static void* main_lib_init_state(module_status& module_status,void**,size_t) {
  LOG_DEBUG("main_lib : main_lib_init_state");
  std::unique_ptr<main_lib> main_lib_guard_ptr = std::make_unique<main_lib>();

  module::library* global_data_library = 0x0;
  module::library* catch_event_library = 0x0;
  { //global_data
    global_data_library = module::init(ROOT_PATH "global_data.so", module_status);
    if (!global_data_library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    main_lib_guard_ptr->libraries.push_back(global_data_library);
  }
  { //catch_event
    catch_event_library = module::init(ROOT_PATH "catch_event.so", module_status);
    if (!catch_event_library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    main_lib_guard_ptr->libraries.push_back(catch_event_library);
  }
  { //update
    module::library* libraries_dependencies[2] = {catch_event_library,
                                              global_data_library};
    module::library* library = module::init(ROOT_PATH "update.so", module_status,
                                            libraries_dependencies, 2);
    if (!library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    main_lib_guard_ptr->libraries.push_back(library);
  }
  { //render
    module::library* libraries_dependencies[1] = {global_data_library};
    module::library* library = module::init(ROOT_PATH "render.so", module_status,
                                            libraries_dependencies, 1);
    if (!library) {
      LOG_ERROR("module::init");
      module_status.error = true;
      return 0x0;
    }
    if (module_status.error) {
      LOG_ERROR("module::init");
      return 0x0;
    }
    main_lib_guard_ptr->libraries.push_back(library);
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
    main_lib_guard_ptr->libraries.push_back(library);
  }

  return main_lib_guard_ptr.release();
}

static module_status main_lib_step(void* state) {
  LOG_DEBUG("main_lib : step");
  assert(state);
  struct main_lib* main_lib =
      static_cast<struct main_lib*>(state);

  for (module::library* library : main_lib->libraries) {
    assert(library);

    // MDTMP revisit loading strategy
    module_status step_status;
    const module_status reload_status =
        module::reload_if_needed(*library);
    if (reload_status.error) {
      LOG_ERROR("reload_if_needed");
      step_status.error = true;
      return step_status;
    }

    step_status = module::step(*library);
    if (step_status.error) {
      LOG_ERROR("step_status.error");
      return step_status;
    }
    if (step_status.info_code == module::STEP_INFO_STOPPING) {
      return step_status;
    }
  }
  return module_status();
}

MODULE_EXPORT_API(main_lib_init_state, 0x0,
                  0x0, 0x0,
                  main_lib_step);
