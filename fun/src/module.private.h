struct module_reload_status{
  bool success = true;
};
static module_reload_status module_reload(module::library& library, const char* module_path)
{
  assert(module_path);
  assert(module_path[0]);

  module_reload_status module_reload_status;

  if (library.library_handle) {
    if( library.api_handle ) {
      library.api_handle->unload_state(library.library_state);
    }
    if ( dlclose(library.library_handle) != 0 ) {
      LOG_ERROR("dlclose : %s", dlerror());
      module_reload_status.success = false;
      return module_reload_status;
    }
  }

  void* library_handle = dlopen(module_path, RTLD_NOW);
  if (!library_handle) {
    LOG_ERROR("dlopen : %s", dlerror());
    module_reload_status.success = false;
    return module_reload_status;
  }

  library.library_handle = library_handle;
  library.api_handle = static_cast<api_handle*>(dlsym(library.library_handle, MODULE_VAR_NAME));
  if (!library.api_handle) {
    LOG_ERROR("dlsym : %s", dlerror());
    dlclose(library.library_handle);
    library.library_handle = NULL;
    module_reload_status.success = false;
    return module_reload_status;
  }

  if (!library.library_state) {
    if( library.api_handle ) {
      library.library_state = library.api_handle->init_state();
    }
  }
  if ( library.api_handle ) {
    library.api_handle->load_state(library.library_state);
  }

  return module_reload_status;
}

void module_unload(module::library& library)
{
  assert(library.library_handle);
  assert(library.api_handle);

  if ( library.api_handle->uninit_state ) {
    library.api_handle->uninit_state(library.library_state);
  }
  library.library_state = NULL;
  dlclose(library.library_handle);
  library.library_handle = NULL;
}
