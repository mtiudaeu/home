#ifndef CORE_DATA_MANAGER_H
#define CORE_DATA_MANAGER_H

#include "core/module.h"

#include <vector>

// MDTMP should be a class? Define access interface
struct data_manager_s {
  data_manager_s();
  ~data_manager_s();
  // MDTMP should have vector in header
  std::vector<module_s*> modules;
};

#endif
