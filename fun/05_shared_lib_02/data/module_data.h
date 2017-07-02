#ifndef CORE_DATA_MODULE_DATA_H
#define CORE_DATA_MODULE_DATA_H

#include "data/data_type.h"

#include "core/module.h"

#include <memory>
#include <vector>

struct module_s;
struct module_data_s {
  DT_ID_HEADER(DT_MODULES);

  std::vector<std::unique_ptr<module_s>> modules;
};

#endif


