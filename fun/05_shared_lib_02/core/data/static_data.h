#ifndef CORE_DATA_STATIC_DATA_H
#define CORE_DATA_STATIC_DATA_H

#include "core/data/data_struct_ids.h"

#include <string>
#include <map>

struct static_data_s {
  //FIXME settle on data structure later (json?).
  std::map<std::string, std::string> data;
};

#endif

