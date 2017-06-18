#ifndef CORE_DATA_HOTKEYS_DATA_H
#define CORE_DATA_HOTKEYS_DATA_H

#include "core/data/data_struct_ids.h"

#include <SDL2/SDL.h>

#include <vector>

struct hotkeys_data_s {
  std::vector<SDL_Event> events;
};

#endif

