#include "data/data_manager.h"

#include "data/module_data.h"
#include "data/game_data.h"

#include <assert.h>

struct imp_s {
  module_data_s module_data;
  game_data_s game_data;
};

data_manager_s::data_manager_s()
 : imp_(new struct imp_s())
{}

data_manager_s::~data_manager_s() {
  assert(imp_);
  delete imp_;
  imp_ = 0x0;
}

void* data_manager_s::get_data(size_t id) {
  switch(id)
  {
    case DSI_MODULES :
      return &imp_->module_data;
    case DSI_DATA :
      return &imp_->game_data;
  }
  LOG_ERROR("Should not rearch here");
  return 0x0;
}
