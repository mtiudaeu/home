#include "core/module_create.h"
#include "core/data_manager.h"

#include <SDL2/SDL.h>

MODULE_DEFAULT_INITIALIZE;

static status_s update_step_cb() {
  assert(data_manager);

  if(data_manager->MDTMP_data["time_current"] == 0) {
    data_manager->MDTMP_data["time_current"] = SDL_GetTicks();
  }

  const int time_new = SDL_GetTicks();
  data_manager->MDTMP_data["time_delta"] =
      time_new - data_manager->MDTMP_data["time_current"];
  data_manager->MDTMP_data["time_current"] = time_new;

  return status_s();
}

MODULE_EXPORT_STEP_CB(update_step_cb);
