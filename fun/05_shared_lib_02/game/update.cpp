#include "core/module_create.h"
#include "core/data_manager.h"

#include <SDL2/SDL.h>

#include <map>
#include <string>

MODULE_DEFAULT_INITIALIZE;

static status_s update_step_cb() {
  assert(data_manager);

  std::map<std::string, int>* data_ptr = static_cast<std::map<std::string, int>*>(
    data_manager->get_data(data_manager_s::ID_DATA));
  assert(data_ptr);
  std::map<std::string, int>& data = *data_ptr;

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
