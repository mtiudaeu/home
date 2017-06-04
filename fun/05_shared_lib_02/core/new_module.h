#ifndef NEW_MODULE_H
#define NEW_MODULE_H

#include "core/status.hpp"

typedef status (*module_init_cb)(data_manager* data_manager);
typedef status (*module_update_cb)();

struct module {
  module_init_cb init_cb = 0x0;
  module_update_cb uninit_cd = 0x0;
  module_update_cb step_cd = 0x0;
  void* lib_handle = 0x0;
  const char* lib_path = 0x0;
  ino_t st_ino = 0;
};

enum step_info { STEP_INFO_RUNNING = 0, STEP_INFO_STOPPING };

#endif
