#include "core/data_manager.h"

#include <assert.h>

// TODO This should be in a global data initilization layout
const char* lib_array[] = {ROOT_PATH "update.so", ROOT_PATH "render.so",
            ROOT_PATH "context.so"};

data_manager_s::data_manager_s() {
  const size_t lib_array_size = sizeof(lib_array) / sizeof(lib_array[0]);
  for (size_t i = 0; i < lib_array_size; ++i) {
    module_s* module = new struct module_s();
    module->lib_path = lib_array[i];
    modules.push_back(module);
  }
}

data_manager_s::~data_manager_s() {
  for (auto module : modules) {
    assert(module);
    //MDTMP what is this type???
    delete module;
    module = 0x0;
  }
  modules.clear();
}
