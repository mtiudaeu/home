#include "new_module_init.h"

struct main_lib {
  data_manager data_manager;
};

static std::unique_ptr<main_lib> init(module_status& module_status) {
  LOG_DEBUG("init");
  std::unique_ptr<main_lib> main_lib_ptr = std::make_unique<main_lib>();

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
    main_lib_ptr->libraries.push_back(global_data_library);
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
    main_lib_ptr->libraries.push_back(catch_event_library);
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
    main_lib_ptr->libraries.push_back(library);
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
    main_lib_ptr->libraries.push_back(library);
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
    main_lib_ptr->libraries.push_back(library);
  }

  return main_lib_ptr;
}

static status step(struct main_lib& main_lib) {
  LOG_DEBUG("main_lib : step");

  for (module::library* library : main_lib.libraries) {
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
    if (step_status.info_code == STEP_INFO_STOPPING) {
      return step_status;
    }
  }
  return module_status();
}

int main() {
  status status;
  std::unique_ptr<main_lib> main_lib_ptr = init(status);
  if (!main_lib_ptr) {
    LOG_ERROR(!main_lib_ptr);
    return 1;
  }
  if (status.error) {
    LOG_ERROR("status.error : %zu", status.info_code);
    return 1;
  }

  for (;;) {
    status = step(*main_lib_ptr);
    if (status.error) {
      LOG_ERROR("status.error : %zu", status.info_code);
      break;
    }
    if (status.info_code == STEP_INFO_STOPPING) {
      LOG_DEBUG("status.info_code == STEP_INFO_STOPPING");
      break;
    }
  }
}
