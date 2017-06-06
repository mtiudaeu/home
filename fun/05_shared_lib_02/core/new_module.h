#ifndef NEW_MODULE_H
#define NEW_MODULE_H

#include "core/status.h"

struct data_manager_s;

typedef status_s (*module_init_cb_t)(data_manager_s* data_manager);
typedef status_s (*module_update_cb_t)();

struct module_s {
  module_init_cb_t init_cb = 0x0;
  module_update_cb_t uninit_cb = 0x0;
  module_update_cb_t step_cb = 0x0;
  void* lib_handle = 0x0;
  const char* lib_path = 0x0;
  ino_t st_ino = 0;
};

enum step_info {
  STEP_INFO_RUNNING = 0,
  STEP_INFO_STOPPING
};

#endif
