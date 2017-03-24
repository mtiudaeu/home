static module_status module_reload(module::library& library, const char* module_path)
{
  assert(module_path);
  assert(module_path[0]);

  module_status reload_status;
  if (library.library_handle) {
    if (library.module_api_handle) {
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

  if (!library.library_state) {
    module_status init_state_status;
    library.library_state =
        library.module_api_handle->init_state(init_state_status);
    if (init_state_status.error) {
      reload_status.error = true;
      return reload_status;
    }
  }
  if (library.module_api_handle->load_state(library.library_state).error) {
    reload_status.error = true;
    return reload_status;
  }

  return reload_status;
}

module_status module_unload(module::library& library)
{
  assert(library.library_handle);
  assert(library.module_api_handle);

  module_status module_status;
  if ( library.module_api_handle->uninit_state ) {
    if ( library.module_api_handle->uninit_state(library.library_state).error) {
module_status.error = true;
}
  }
  library.library_state = NULL;
  dlclose(library.library_handle);
  library.library_handle = NULL;
return module_status;
}
