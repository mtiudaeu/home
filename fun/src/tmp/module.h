#include <sys/types.h>

#define API_NAME "MODULE_API"

//MDTMP move inside namespace?
struct api_handle {
    void *(*init_state)() = 0x0;
    void (*uninit_state)(void *state) = 0x0;
    void (*load_state)(void *state) = 0x0;
    void (*unload_state)(void *state) = 0x0;
    bool (*step)(void *state) = 0x0;
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
