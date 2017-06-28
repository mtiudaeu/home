#include "data/data_manager.h"

#include "data/module_data.h"
#include "data/game_data.h"

#include <map>

#include <assert.h>

namespace {
void* create_data_type(data_type_e type_id) {
  switch (type_id) {
    case DT_MODULES:
      return new struct module_data_s();
    case DT_GAME:
      return new struct game_data_s();
  }
  LOG_ERROR("Should not rearch here");
  return 0x0;
}
}

struct imp_s {
  std::map<std::string, void*> data;
};

data_manager_s::data_manager_s()
 : imp_(new struct imp_s())
{}

data_manager_s::~data_manager_s() {
  assert(imp_);
  delete imp_;
  imp_ = 0x0;
}

void* data_manager_s::get_data(const std::string path,
                               data_type_e type_id) {
  auto it = imp_->data.find(path);
  if (it == imp_->data.end()) {
      auto ret = imp_->data.insert({path, create_data_type(type_id)});
      if (!ret.second) {
        LOG_ERROR("imp_->data.insert");
      }
      it = ret.first;
  }
  return it->second;
}

