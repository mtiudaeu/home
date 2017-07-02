#ifndef CORE_MODULE_H
#define CORE_MODULE_H

#include "core/module_create.h"

struct module_s {
  module_init_cb_t init_cb = 0x0;
  module_update_cb_t uninit_cb = 0x0;
  module_update_cb_t step_cb = 0x0;
  void* lib_handle = 0x0;
  const char* lib_path = 0x0;
  ino_t st_ino = 0;
};

#endif
