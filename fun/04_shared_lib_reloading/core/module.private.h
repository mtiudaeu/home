static module_status module_reload(module::library& library,
                                   const char* module_path,
                                   module::library** dependencies_library_array = 0x0,
                                   size_t dependencies_length = 0)
{
  assert(module_path);
  assert(module_path[0]);

  module_status reload_status;
  { // clean existing library handle
    if (library.library_handle) {
      if (library.module_api_handle && library.module_api_handle->unload_state) {
        if (library.module_api_handle->unload_state(library.library_state)
                .error) {
          LOG_ERROR("unload_state");
          reload_status.error = true;
          return reload_status;
        }
      }
      if (dlclose(library.library_handle) != 0) {
        LOG_ERROR("dlclose : %s", dlerror());
        reload_status.error = true;
        library.library_handle = 0x0;
        return reload_status;
      }
      library.library_handle = 0x0;
    }
  }

  { // create new library handle
    library.library_handle = dlopen(module_path, RTLD_NOW);
    if (!library.library_handle) {
      LOG_ERROR("dlopen : %s", dlerror());
      reload_status.error = true;
      return reload_status;
    }

    library.module_api_handle = static_cast<module_api_handle*>(
        dlsym(library.library_handle, MODULE_VAR_NAME));
    if (!library.module_api_handle) {
      LOG_ERROR("dlsym : %s", dlerror());
      dlclose(library.library_handle);
      library.library_handle = NULL;
      reload_status.error = true;
      return reload_status;
    }
  }

  { // create library data (only once)
    if (!library.library_state && library.module_api_handle->init_state) {
      module_status init_state_status;
      void* library_states_array[dependencies_length];
      void** library_states_array_ptr = 0x0; //Stays null if array is of 0 elements.
      for (size_t i = 0; i < dependencies_length; ++i) {
        if (module::library* library_dep = dependencies_library_array[i]) {
          library_states_array[i] = library_dep->library_state;
        } else {
          LOG_ERROR("!library_dep");
          library_states_array[i] = 0x0;
        }
        library_states_array_ptr = library_states_array;
      }
      library.library_state = library.module_api_handle->init_state(
          init_state_status, library_states_array_ptr, dependencies_length);
      if (init_state_status.error) {
        reload_status.error = true;
        return reload_status;
      }
    }
  }

  { // load library data in new library handle
    if (library.library_state && library.module_api_handle->load_state) {
      if (library.module_api_handle->load_state(library.library_state).error) {
        reload_status.error = true;
        return reload_status;
      }
    }
  }

  return reload_status;
}

