#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "core/new_module.h"

#include <vector>

// MDTMP should be a class? Define access interface
struct data_manager_s {
  data_manager_s();
  ~data_manager_s();
  // MDTMP should have vector in header
  std::vector<module_s*> modules;
};

#endif
