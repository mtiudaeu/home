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
  size_t info_code = 0;
};

typedef void* (*module_state_init_cb)(module_status&,
                                      void** dependencies_state_array,
                                      size_t dependencies_length);
typedef module_status (*module_state_update_cb)(void* state);
// module callbacks
struct module_api_handle {
  module_api_handle(module_state_init_cb init_state,
                    module_state_update_cb uninit_state,
                    module_state_update_cb load_state,
                    module_state_update_cb unload_state,
                    module_state_update_cb step)
      : init_state(init_state),
        uninit_state(uninit_state),
        load_state(load_state),
        unload_state(unload_state),
        step(step) {}

  module_state_init_cb init_state;
  module_state_update_cb uninit_state;
  module_state_update_cb load_state;
  module_state_update_cb unload_state;
  module_state_update_cb step;
};

namespace module {
struct library;
library* init(const char* module_path, module_status& module_status,
              module::library** dependencies_library_array = 0x0,
              size_t dependencies_length = 0);
module_status uninit(library* library);

module_status reload_if_needed(library& library);
enum step_info { STEP_INFO_RUNNING = 0, STEP_INFO_STOPPING };
module_status step(library& library);
}

#endif
