#include "module.h"

#include <stdio.h>
#include <dlfcn.h>
#include <sys/stat.h>

void module::load(struct module& module, const char* module_path)
{
  assert(module_path);
  assert(module_path[0]);

  struct stat stat;
  if (stat(module_path, &stat) != 0) {
    // MDTMP error?
    return;
  }

  if (module.library_handle) {
    // unload library
    // MDTMP module.api_handle.unload(module.library_state);
    dlclose(module.library_handle);
  }

  void* library_handle = dlopen(module_path, RTLD_NOW);
  if (!library_handle) {
    // MDTMP error?
    module.st_ino = 0;
    return;
  }

  module.library_handle = library_handle;
  module.st_ino = stat.st_ino;
  void* api_handle = dlsym(module.library_handle, "GAME_API");
  if (!api_handle) {
    // MDTMP error
    dlclose(module.library_handle);
    module.library_handle = NULL;
    module.st_ino = 0;
    return;
  }

  module.api_handle = api_handle;
  if (!module.library_state) {
    // MDTMP module.library_state = module.api_handle.init();
  }
  // MDTMP module.api_handle.reload(module.library_state);
}

void module::unload(struct module& module)
{
  if (!module.library_handle) {
    // MDTMP error
    return;
  }

//MDTMP put into a function and reuse for error above?
  module.api_handle.finalize(module.library_state);
  module.library_state = NULL;
  dlclose(module.library_handle);
  module.library_handle = NULL;
  module.st_ino = 0;
}

