#ifndef MODULE_H
#define MODULE_H

#include <sys/types.h>

#define MODULE_VAR_NAME "MODULE_API"
#define MODULE_EXPORT_API(init_state, uninit_state, load_state, unload_state, \
                          step)                                               \
  extern const struct module_api_handle MODULE_API(init_state, uninit_state,         \
                                            load_state, unload_state, step);

// FIXME move in namespace?
struct module_api_handle {
  module_api_handle(void* (*init_state)(), void (*uninit_state)(void* state),
             void (*load_state)(void* state), void (*unload_state)(void* state),
             bool (*step)(void* state))
      : init_state(init_state),
        uninit_state(uninit_state),
        load_state(load_state),
        unload_state(unload_state),
        step(step) {}

//MDTMP All should return errors
  void* (*init_state)();
  void (*uninit_state)(void* state);
  void (*load_state)(void* state);
  void (*unload_state)(void* state);
  bool (*step)(void* state);
};

namespace module {

struct library;

library* init(const char* module_path);
void uninit(library* library);

struct reload_status {
  bool reload_needed = false;
  bool reload_succeeded = true;
};
reload_status reload_if_needed(library& library);

//MDTMP move this up should be the return value of module_api_handle.step()
struct step_status {
  bool stepping_done = false;
};
step_status step(library& library);

}

#endif
