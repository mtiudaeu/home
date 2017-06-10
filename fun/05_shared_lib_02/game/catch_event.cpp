#include "core/log.h"
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
      std::map<std::string, int>* data_ptr = static_cast<std::map<std::string, int>*>(
        data_manager->get_data(data_manager_s::ID_DATA));
      assert(data_ptr);
      std::map<std::string, int>& data = *data_ptr;
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
