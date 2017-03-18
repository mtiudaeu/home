#include "module.h"

#include "log.h"

#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>

namespace module {
struct library {
  void* library_handle = 0x0;
  struct api_handle* api_handle = 0x0;
  void* library_state = 0x0;
};
}

#include "module.private.h"

module::library* module::init(const char* module_path)
{
   module::library* library = new module::library();
//MDTMP this could fail.
   module_load(*library, module_path);
   return library;
}

void module::uninit(module::library* library)
{
   assert(library);
   module_unload(*library);
   delete library;
}

module::step_status module::step(module::library& library)
{
  module::step_status step_status;
  if (!library.api_handle) {
    LOG_ERROR("!library.api_handle");
    step_status.stepping_done = true;
    return step_status;
  }

  library.api_handle->step(library.library_state);
  return step_status;
}

