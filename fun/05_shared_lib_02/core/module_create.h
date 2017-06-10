#ifndef CORE_MODULE_CREATE_H
#define CORE_MODULE_CREATE_H

#include "core/status.h"
#include "core/data_manager.h"

#include <assert.h>

#define MODULE_VAR_NAME "MODULE_CALLBACKS"
#define MODULE_EXPORT(init_cb, uninit_cb, step_cb)                                         \
  extern const struct module_callbacks_s MODULE_CALLBACKS(init_cb, uninit_cb, step_cb)
#define MODULE_EXPORT_STEP_CB(step_cb)                                         \
  extern const struct module_callbacks_s MODULE_CALLBACKS(module_default_init_cb, module_default_uninit_cb, step_cb)

typedef status_s (*module_init_cb_t)(data_manager_s* data_manager);
typedef status_s (*module_update_cb_t)();

struct module_callbacks_s {
  module_callbacks_s(module_init_cb_t init_cb,
                   module_update_cb_t uninit_cb,
                   module_update_cb_t step_cb)
      : init_cb(init_cb), uninit_cb(uninit_cb), step_cb(step_cb) {}

  module_init_cb_t init_cb;
  module_update_cb_t uninit_cb;
  module_update_cb_t step_cb;
};

#define MODULE_DEFAULT_INITIALIZE            \
  static data_manager_s* data_manager = 0x0; \
  MODULE_DEFAULT_INIT_CB;                    \
  MODULE_DEFAULT_UNINIT_CB;

#define MODULE_DEFAULT_INIT_CB                                   \
  static status_s module_default_init_cb(data_manager_s* data) { \
    data_manager = data;                                         \
    assert(data_manager);                                        \
    return status_s();                                           \
  }
#define MODULE_DEFAULT_UNINIT_CB               \
  static status_s module_default_uninit_cb() { \
    assert(data_manager);                      \
    data_manager = 0x0;                        \
    return status_s();                         \
  }

enum step_info {
  STEP_INFO_RUNNING = 0,
  STEP_INFO_STOPPING,
};

#endif
