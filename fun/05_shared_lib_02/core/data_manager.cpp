#include "core/data_manager.h"
#include "core/module.h"
#include "core/log.h"

#include <vector>
#include <map>
#include <string>

//FIXME hack fix this
struct imp_s {
  std::vector<module_s*> modules;
  std::map<std::string, int> data;
};

// TODO This should be in a global data initilization layout
const char* lib_array[] = {ROOT_PATH "game_context.so",
                           ROOT_PATH "game_catch_event.so",
                           ROOT_PATH "game_update.so",
                           ROOT_PATH "game_render.so"};

data_manager_s::data_manager_s()
 : imp_(std::make_unique<imp_s>())
{
  //MDTMP should be initialize by module_manager
  const size_t lib_array_size = sizeof(lib_array) / sizeof(lib_array[0]);
  for (size_t i = 0; i < lib_array_size; ++i) {
    module_s* module = new struct module_s();
    module->lib_path = lib_array[i];
    imp_->modules.push_back(module);
  }
}

data_manager_s::~data_manager_s() {
  for (auto module : imp_->modules) {
    assert(module);
    //MDTMP what is this type???
    delete module;
    module = 0x0;
  }
  imp_->modules.clear();
}

void* data_manager_s::get_data(size_t id) {
  switch(id)
  {
    case ID_MODULES :
      return &imp_->modules;
    case ID_DATA :
      return &imp_->data;
  }
  LOG_ERROR("Should not rearch here");
  return 0x0;
}
