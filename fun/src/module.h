#include <sys/types.h>

#define MODULE_VAR_NAME "MODULE_API"
#define MODULE_EXPORT_API(init_state, uninit_state, load_state, unload_state, \
                          step)                                               \
  extern const struct api_handle MODULE_API(init_state, uninit_state,         \
                                            load_state, unload_state, step);


//MDTMP move inside namespace?
struct api_handle {
  api_handle(
  void* (*init_state)(),
  void (*uninit_state)(void* state),
  void (*load_state)(void* state),
  void (*unload_state)(void* state),
  bool (*step)(void* state)
)
      : init_state(init_state),
        uninit_state(uninit_state),
        load_state(load_state),
        unload_state(unload_state),
        step(step) {}

  void* (*init_state)();
  void (*uninit_state)(void* state);
  void (*load_state)(void* state);
  void (*unload_state)(void* state);
  bool (*step)(void* state);
};

namespace module {

struct library {
  void* library_handle = 0x0;
  void* library_state = 0x0;
  struct api_handle* api_handle = 0x0;
};

void load(struct library& library, const char* module_path);
void unload(struct library& library);

}
