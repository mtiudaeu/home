#include "core/data/hotkeys_data.h"

#include "core/module_create.h"

#include <SDL2/SDL.h>

MODULE_DEFAULT_INITIALIZE;

static status_s catch_event_step_cb() {
  assert(data_manager);

  status_s step_status;
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      LOG_DEBUG("Quit event detected");
      step_status.info_code = STEP_INFO_STOPPING;
      return step_status;
    }
    if (ev.type == SDL_KEYDOWN) {
      hotkeys_data_s* hotkeys_data = static_cast<hotkeys_data_s*>(
        data_manager->get_data(DSI_HOTKEYS));
      assert(hotkeys_data);
      auto& events = hotkeys_data->events;
      events.push_back(ev);
    }
  }

  return status_s();
}

MODULE_EXPORT_STEP_CB(catch_event_step_cb);
