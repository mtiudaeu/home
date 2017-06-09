#include "core/log.h"
#include "core/module_create.h"
#include "core/data_manager.h"

#include <SDL2/SDL.h>

#include <assert.h>

static data_manager_s* data_manager = 0x0;

MODULE_DEFAULT_INIT_CB;

MODULE_DEFAULT_UNINIT_CB;

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
      switch (ev.key.keysym.sym) {
        case SDLK_LEFT:
          data_manager->MDTMP_data["posx"] -= 1;
          break;
        case SDLK_RIGHT:
          data_manager->MDTMP_data["posx"] += 1;
          break;
        case SDLK_UP:
          data_manager->MDTMP_data["posy"] += 1;
          break;
        case SDLK_DOWN:
          data_manager->MDTMP_data["posy"] -= 1;
          break;
      }
    }
  }

  return status_s();
}

MODULE_EXPORT(module_default_init_cb, module_default_uninit_cb, catch_event_step_cb);
