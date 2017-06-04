#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "core/new_module.h"

class data_manager {
  data_manager();
  ~data_manager();
  std::vector<module*> modules;
};

#endif

