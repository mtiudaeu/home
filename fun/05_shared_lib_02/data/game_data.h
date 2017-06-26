#ifndef CORE_DATA_GAME_DATA_H
#define CORE_DATA_GAME_DATA_H

#include "data/data_type.h"

#include <string>
#include <map>

struct game_data_s {
  DT_ID_HEADER(DT_GAME);

  std::map<std::string, int> data;
};

#endif

