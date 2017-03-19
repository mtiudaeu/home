#include "module.h"

#include "log.h"

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
  struct api_handle* api_handle = 0x0;
  void* library_state = 0x0;
  ino_t st_ino = 0;
  std::string path;
};
}

#include "module.private.h"

module::library* module::init(const char* module_path) {
  assert(module_path);
  assert(module_path[0]);

  struct stat attr;
  if (stat(module_path, &attr) != 0) {
    LOG_ERROR("%s", strerror(errno));
    return 0x0;
  }

  module::library* library = new module::library();
  if (module_reload(*library, module_path).success == false) {
    delete library;
    return 0x0;
  }
  
  library->st_ino = attr.st_ino;
  library->path = module_path;
  return library;
}

void module::uninit(module::library* library) {
  assert(library);
  module_unload(*library);
  delete library;
}

module::step_status module::step(module::library& library) {
  assert(library.api_handle);

  module::step_status step_status;
  struct stat attr;
  if (stat(library.path.c_str(), &attr) == 0 && attr.st_ino != library.st_ino) {
    // file changed -> reload library
    if (module_reload(library, library.path.c_str()).success == false) {
      step_status.stepping_done = true;
      return step_status;
    }
    library.st_ino = attr.st_ino;
  }

  // FIXME this should be able to fail/end
  library.api_handle->step(library.library_state);
  return step_status;
}
