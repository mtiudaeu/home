#include "core/data/data_manager.h"

#include "core/data/module_data.h"
#include "core/data/runtime_data.h"
#include "core/data/static_data.h"
#include "core/data/hotkeys_data.h"

#include <assert.h>

struct imp_s {
  module_data_s module_data;
  runtime_data_s runtime_data;
  static_data_s static_data;
  hotkeys_data_s hotkeys_data;
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
    case DSI_RUNTIME :
      return &imp_->runtime_data;
    case DSI_STATIC :
      return &imp_->static_data;
    case DSI_HOTKEYS :
      return &imp_->hotkeys_data;
  }
  LOG_ERROR("Should not rearch here");
  return 0x0;
}
