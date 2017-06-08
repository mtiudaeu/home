#ifndef CORE_MODULE_CREATE_H
#define CORE_MODULE_CREATE_H

#include "core/status.h"

#define MODULE_VAR_NAME "MODULE_CALLBACKS"
#define MODULE_EXPORT(init_cb, uninit_cb, step_cb)                                         \
  extern const struct module_callbacks_s MODULE_CALLBACKS(init_cb, uninit_cb, step_cb)

struct data_manager_s;
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

#endif
