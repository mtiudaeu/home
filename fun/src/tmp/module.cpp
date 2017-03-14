#include "module.h"

#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>
#include <assert.h>

void module::load(struct library& library, const char* module_path)
{
  assert(module_path);
  assert(module_path[0]);

  struct stat stat;
  if (stat(module_path, &stat) != 0) {
    // FIXME error?
    return;
  }

  if (library.library_handle) {
    // unload library
    library.api_handle->unload(library.library_state);
    dlclose(library.library_handle);
  }

  void* library_handle = dlopen(module_path, RTLD_NOW);
  if (!library_handle) {
    // MDTMP error?
    library.st_ino = 0;
    return;
  }

  library.library_handle = library_handle;
  library.st_ino = stat.st_ino;
  library.api_handle = static_cast<api_handle*>(dlsym(library.library_handle, MODULE_API));
  if (!library.api_handle) {
    // MDTMP error
    dlclose(library.library_handle);
    library.library_handle = NULL;
    library.st_ino = 0;
    return;
  }

  if (!library.library_state) {
    library.library_state = library.api_handle->init_state();
  }
  library.api_handle->load(library.library_state);
}

void module::unload(struct library& library)
{
  if (!library.library_handle) {
    // MDTMP error
    return;
  }

  //MDTMP uninitialize in function for reuser for error cases.
  library.api_handle->uninit_state(library.library_state);
  library.library_state = NULL;
  dlclose(library.library_handle);
  library.library_handle = NULL;
  library.st_ino = 0;
}

