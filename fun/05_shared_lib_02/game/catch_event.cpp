#include "data/game_data.h"

#include "core/module_create.h"

#include <SDL2/SDL.h>

#include <map>
#include <string>

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
      game_data_s* game_data = static_cast<game_data_s*>(
        data_manager->get_data(DSI_DATA));
      assert(game_data);
      std::map<std::string, int>& data = game_data->data;
      switch (ev.key.keysym.sym) {
        case SDLK_LEFT:
          data["posx"] -= 1;
          break;
        case SDLK_RIGHT:
          data["posx"] += 1;
          break;
        case SDLK_UP:
          data["posy"] += 1;
          break;
        case SDLK_DOWN:
          data["posy"] -= 1;
          break;
      }
    }
  }

  return status_s();
}

MODULE_EXPORT_STEP_CB(catch_event_step_cb);
