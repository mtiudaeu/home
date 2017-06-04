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
                              module::library** dependencies_library_array,
                              size_t dependencies_length) {
  assert(module_path);
  assert(module_path[0]);

  struct stat attr;
  { // check file exist
    if (stat(module_path, &attr) != 0) {
      LOG_ERROR("%s : %s", strerror(errno), module_path);
      module_status.error = true;
      return 0x0;
    }
  }

  module::library* library = new module::library();
  { // create library
    if (module_reload(*library, module_path, dependencies_library_array,
                      dependencies_length).error) {
      LOG_ERROR("module_reload");
      delete library;
      module_status.error = true;
      return 0x0;
    }
    
    library->st_ino = attr.st_ino;
    library->path = module_path;
  }
  return library;
}

module_status module::uninit(module::library* library) {
  assert(library);
  assert(library->library_handle);
  assert(library->module_api_handle);

  module_status module_status;
  { // uninit state
    if (library->module_api_handle->uninit_state) {
      module_status = library->module_api_handle->uninit_state(library->library_state);
    }
    library->library_state = NULL;
  }

  { // uninit library handle
    dlclose(library->library_handle);
    library->library_handle = NULL;
    delete library;
    library = 0x0;
  }

  return module_status;
}

module_status module::reload_if_needed(library& library)
{
  module_status reload_status;
  struct stat attr;
  { // get file info
    if (stat(library.path.c_str(), &attr) != 0) {
      LOG_ERROR("%s : %s", strerror(errno), library.path.c_str());
      return reload_status;
    }
  }

  if (attr.st_ino == library.st_ino) {
    // file didn't changed, do not reload.
    return reload_status;
  }

  // FIXME : We assume that the shared library is fully writted.
  // If it is not done compiling, it can still be seen as a different
  // file and loading will failed.
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

  if( library.module_api_handle->step ) {
    return library.module_api_handle->step(library.library_state);
  }
  return module_status();
}
