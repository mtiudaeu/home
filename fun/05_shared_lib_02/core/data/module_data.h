#ifndef CORE_DATA_MODULE_DATA_H
#define CORE_DATA_MODULE_DATA_H

#include "core/data/data_struct_ids.h"

#include "core/module.h"

#include <memory>
#include <vector>

struct module_s;
struct module_data_s {
  std::vector<std::unique_ptr<module_s>> modules;
};

#endif


