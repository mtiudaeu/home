#include "global_data.h"

#include "module.h"

#include <assert.h>

static void* global_data_init_state(module_status&, void**, size_t) {
  return new struct global_data();
}

static module_status global_data_uninit(void* state)
{
  assert(state);
  global_data* global_data = static_cast<struct global_data*>(state);
  delete global_data;

  return module_status();
}

MODULE_EXPORT_API(global_data_init_state, global_data_uninit, 0x0,
                  0x0, 0x0);
