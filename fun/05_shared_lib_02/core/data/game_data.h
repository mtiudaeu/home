#ifndef CORE_DATA_GAME_DATA_H
#define CORE_DATA_GAME_DATA_H

#include "core/data/data_struct_ids.h"

#include <string>
#include <map>

struct game_data_s {
  std::map<std::string, int> data;
};

#endif

