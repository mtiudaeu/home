#include "core/data_manager.h"

#include "core/new_module.h"

#include "core/status.h"

status init_module(module& module, data_manager& data_manager)
{
  status status;
  auto clean_up_func = [&] {
    dlclose(module.lib_handle);
    module.lib_handle = 0x0;
    module.init_cb = 0x0;
    module.uninit_cd = 0x0;
    module.step_cd = 0x0;
    module.st_ino = 0;

    status.error = true;
  };

  if(!module.lib_path) {
    LOG_DEBUG("!module.lib_path"):
    return status;
  }

  struct stat attr;
  if (stat(module.lib_path, &attr) != 0) {
    LOG_ERROR("%s : %s", strerror(errno), module.lib_path);
    return status;
  }

  module.lib_handle = dlopen(module.lib_path, RTLD_NOW);
  if (!module.lib_handle) {
    LOG_ERROR("dlopen : %s", dlerror());
    status.error = true;
    return status;
  }
  module.st_ino = attr.st_ino;

  module.init_cb = static_cast<module_init_cb*>(
      dlsym(module.lib_handle, "init"));
  if (!module.init_cb) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_func();
    return status;
  }

  module.uninit_cb = static_cast<module_init_cb*>(
      dlsym(module.lib_handle, "uninit"));
  if (!module.uninit_cb) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_func();
    return status;
  }

  module.step_cb = static_cast<module_init_cb*>(
      dlsym(module.lib_handle, "step"));
  if (!module.step_cb) {
    LOG_ERROR("dlsym : %s", dlerror());
    clean_up_func();
    return status;
  }

  status = module.init_cb(&data_manager);
  if(status.error) {
    LOG_ERROR("module.init_cb");
    clean_up_func();
    return status;
  }

  return status;
}

status init_all_module(data_manager& data_manager) {
  status status;
  for( module : data_manager.modules) {
    assert(module);
    status local_status = init_module(*module, data_manager);
    if(local_status.error) {
      LOG_ERROR("local_status.error");
    }
  }
  return status;
}

