#ifndef CORE_DATA_MANAGER_H
#define CORE_DATA_MANAGER_H

#include "core/module.h"

#include <vector>
#include <map>
#include <string>

// MDTMP should be a class? Define access interface
struct data_manager_s {
  data_manager_s();
  ~data_manager_s();
  // MDTMP should not have vector in header
  std::vector<module_s*> modules;
  // MDTMP should not have map in header
  // MDTMP should not have string in header
  std::map<std::string, int> MDTMP_data;
};

#endif
