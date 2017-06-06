#ifndef NEW_MODULE_INIT_H
#define NEW_MODULE_INIT_H

#include "core/new_module.h"

#include "core/status.h"
#include "core/data_manager.h"

#include <dlfcn.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

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

  module.init_cb =
      static_cast<module_init_cb_t>(dlsym(module.lib_handle, "init"));
  if (!module.init_cb) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_module();
    status.error = true;
    return status;
  }

  module.uninit_cb =
      static_cast<module_init_cb_t>(dlsym(module.lib_handle, "uninit"));
  if (!module.uninit_cb) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_module();
    status.error = true;
    return status;
  }

  module.step_cb =
      static_cast<module_init_cb_t>(dlsym(module.lib_handle, "step"));
  if (!module.step_cb) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_module();
    status.error = true;
    return status;
  }

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
  for (auto module : data_manager.modules) {
    assert(module);
    status_s local_status = init_module(*module, data_manager);
    if (local_status.error) {
      LOG_ERROR("local_status.error");
    }
  }
  return status;
}

#endif
