#ifndef CORE_MODULE_INIT_H
#define CORE_MODULE_INIT_H

#include "data/module_data.h"

#include "core/module.h"

#include <vector>

#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

status_s init_module(module_s& module, data_manager_s& data_manager) {
  auto clean_up_module = [&module] {
    dlclose(module.lib_handle);
    module.lib_handle = 0x0;
    module.init_cb = 0x0;
    module.uninit_cb = 0x0;
    module.step_cb = 0x0;
    module.st_ino = 0;
  };

  status_s status;
  if (!module.lib_path) {
    LOG_DEBUG("!module.lib_path");
    return status;
  }

  struct stat attr;
  if (stat(module.lib_path, &attr) != 0) {
    LOG_ERROR("%s : %s", strerror(errno), module.lib_path);
    return status;
  }

  if (module.st_ino == attr.st_ino) {
    LOG_DEBUG("Don't need reloading");
    return status;
  }
  if (module.st_ino != 0) {
    // module is open. uninit before init
    if (module.uninit_cb) {
      status = module.uninit_cb();
      clean_up_module();
    }
  }

  module.lib_handle = dlopen(module.lib_path, RTLD_NOW);
  if (!module.lib_handle) {
    LOG_ERROR("dlopen : %s", dlerror());
    status.error = true;
    return status;
  }
  module.st_ino = attr.st_ino;

  
  module_callbacks_s* module_callbacks = static_cast<module_callbacks_s*>(
      dlsym(module.lib_handle, MODULE_VAR_NAME));
  if(!module_callbacks) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_module();
    status.error = true;
    return status;
  }

  module.init_cb = module_callbacks->init_cb;
  module.uninit_cb = module_callbacks->uninit_cb;
  module.step_cb = module_callbacks->step_cb;

  status = module.init_cb(&data_manager);
  if (status.error) {
    LOG_ERROR("module.init_cb");
    clean_up_module();
    status.error = true;
    return status;
  }

  return status;
}

status_s init_all_module(data_manager_s& data_manager) {
  status_s status;

  module_data_s* module_data = static_cast<module_data_s*>(
    data_manager.get_data(DSI_MODULES));
  assert(module_data);
  for (const auto& module : module_data->modules) {
    assert(module);
    status_s local_status = init_module(*module, data_manager);
    if (local_status.error) {
      LOG_ERROR("local_status.error");
    }
  }
  return status;
}

#endif
