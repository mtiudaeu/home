#include "core/data/runtime_data.h"

#include "core/module_create.h"

#include <SDL2/SDL.h>

#include <cstdio>

MODULE_DEFAULT_INITIALIZE;

static status_s update_step_cb() {
  assert(data_manager);

  runtime_data_s* runtime_data = static_cast<runtime_data_s*>(
    data_manager->get_data(DSI_RUNTIME));
  assert(runtime_data);
  auto& data = runtime_data->data;

  char buffer [33];
  if(data["time_current"].empty()) {
    sprintf(buffer, "%d", SDL_GetTicks());
    data["time_current"] = buffer;
  }

  int time_current = atoi(data["time_current"].c_str());
  const int time_new = SDL_GetTicks();
  const int time_delta = time_new - time_current;
  sprintf(buffer, "%d", time_new);
  data["time_current"] = buffer;
  sprintf(buffer, "%d", time_delta);
  data["time_delta"] = buffer;

  return status_s();
}

MODULE_EXPORT_STEP_CB(update_step_cb);
