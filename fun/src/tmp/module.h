#include <sys/types.h>

namespace module {

struct module {
  ino_t st_ino;
  void* library_handle;
  void* api_handle;
  void* library_state;
};

void load(struct module& module, const char* module_path);
void unload(struct module& module);

}
