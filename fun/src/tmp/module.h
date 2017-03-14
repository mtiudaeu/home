#include <sys/types.h>

#define MODULE_API "MODULE_API"

namespace module {

struct api_handle {
    void *(*init_state)();
    void (*uninit_state)(void *state);

    void (*load)(void *state);
    void (*unload)(void *state);

    bool (*step)(void *state);
};

struct library {
  ino_t st_ino;
  void* library_handle;
  void* library_state;
  struct api_handle* api_handle;
};

void load(struct library& library, const char* module_path);
void unload(struct library& library);

}
