#ifndef MODULE_H
#define MODULE_H

#include <sys/types.h>

#define MODULE_VAR_NAME "MODULE_API"
#define MODULE_EXPORT_API(init_state, uninit_state, load_state, unload_state, \
                          step)                                               \
  extern const struct module_api_handle MODULE_API(init_state, uninit_state,         \
                                            load_state, unload_state, step);

struct module_status{
  bool error = false;
  size_t info_code = 0; //opaque info code
};
struct module_api_handle {
  module_api_handle(void* (*init_state)(module_status&,
                      void* dependancies_state_array,
                      size_t dependancies_length),
                    module_status (*uninit_state)(void* state),
                    module_status (*load_state)(void* state),
                    module_status (*unload_state)(void* state),
                    module_status (*step)(void* state))
      : init_state(init_state),
        uninit_state(uninit_state),
        load_state(load_state),
        unload_state(unload_state),
        step(step) {}

  void* (*init_state)(module_status& module_status,
                      void* dependancies_state_array,
                      size_t dependancies_length);
  module_status (*uninit_state)(void* state);
  module_status (*load_state)(void* state);
  module_status (*unload_state)(void* state);
  module_status (*step)(void* state);
};

namespace module {
struct library;
library* init(const char* module_path, module_status& module_status,
              void* dependancies_state_array = 0x0, size_t dependancies_length = 0);
module_status uninit(library* library);

module_status reload_if_needed(library& library);
enum step_info { STEP_INFO_RUNNING = 0, STEP_INFO_STOPPING };
module_status step(library& library);
}

#endif
