#include "core/log.h"
#include "core/module.h"

#include <string>

#include <assert.h>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

namespace module {
struct library {
  void* library_handle = 0x0;
  struct module_api_handle* module_api_handle = 0x0;
  void* library_state = 0x0;
  ino_t st_ino = 0;
  std::string path;
};
}

#include "core/module.private.h"

module::library* module::init(const char* module_path,
                              module_status& module_status,
                              module::library** dependancies_library_array,
                              size_t dependancies_length) {
  assert(module_path);
  assert(module_path[0]);

  struct stat attr;
  if (stat(module_path, &attr) != 0) {
    LOG_ERROR("%s : %s", strerror(errno), module_path);
    module_status.error = true;
    return 0x0;
  }

  module::library* library = new module::library();
  if (module_reload(*library, module_path, dependancies_library_array,
                    dependancies_length).error) {
    LOG_ERROR("module_reload")
    delete library;
    module_status.error = true;
    return 0x0;
  }
  
  library->st_ino = attr.st_ino;
  library->path = module_path;
  return library;
}

module_status module::uninit(module::library* library) {
  assert(library);
  module_status module_status = module_unload(*library);
  delete library;
  return module_status;
}

module_status module::reload_if_needed(library& library)
{
  module_status reload_status;
  struct stat attr;
  if (stat(library.path.c_str(), &attr) != 0) {
    LOG_ERROR("%s : %s", strerror(errno), library.path.c_str());
    return reload_status;
  }

  if (attr.st_ino == library.st_ino) {
    // file didn't changed, do not reload.
    return reload_status;
  }

  // Here we assume that the shared library is fully writted.
  // If it is being compiled, it is going to be seen as a different file
  // and loading will fail.
  if (module_reload(library, library.path.c_str()).error) {
    LOG_ERROR("module_reload");
    reload_status.error = true;
    return reload_status;
  }

  library.st_ino = attr.st_ino;
  return reload_status;
}

module_status module::step(module::library& library) {
  assert(library.module_api_handle);

  module_status module_status;

  if( library.module_api_handle->step ) {
    module_status = library.module_api_handle->step(library.library_state);
  }
  return module_status;
}
