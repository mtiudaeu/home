#include "data/game_data.h"

#include "core/module_create.h"

#include <SDL2/SDL.h>

#include <map>
#include <string>

MODULE_DEFAULT_INITIALIZE;

static status_s update_step_cb() {
  assert(data_manager);

  game_data_s* game_data = static_cast<game_data_s*>(
    data_manager->get_data("game", DT_GAME));
  assert(game_data);
  std::map<std::string, int>& data = game_data->data;

  if(data["time_current"] == 0) {
    data["time_current"] = SDL_GetTicks();
  }

  const int time_new = SDL_GetTicks();
  data["time_delta"] =
      time_new - data["time_current"];
  data["time_current"] = time_new;

  return status_s();
}

MODULE_EXPORT_STEP_CB(update_step_cb);
