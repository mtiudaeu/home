#include "module.h"

#include "common/log/log.h"

#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>

void module::load(struct library& library, const char* module_path)
{
  assert(module_path);
  assert(module_path[0]);

  if (library.library_handle) {
    // unload library
    library.api_handle->unload_state(library.library_state);
    dlclose(library.library_handle);
  }

  void* library_handle = dlopen(module_path, RTLD_NOW);
  if (!library_handle) {
    LOG_ERROR("dlopen : %s", dlerror());
    return;
  }

  library.library_handle = library_handle;
  library.api_handle = static_cast<api_handle*>(dlsym(library.library_handle, MODULE_VAR_NAME));
  if (!library.api_handle) {
    LOG_ERROR("dlsym : %s", dlerror());
    dlclose(library.library_handle);
    library.library_handle = NULL;
    return;
  }

  if (!library.library_state) {
    library.library_state = library.api_handle->init_state();
  }
  library.api_handle->load_state(library.library_state);
}

void module::unload(struct library& library)
{
  if (!library.library_handle) {
    return;
  }

  //MDTMP uninitialize in function for reuser for error cases.
  library.api_handle->uninit_state(library.library_state);
  library.library_state = NULL;
  dlclose(library.library_handle);
  library.library_handle = NULL;
}

