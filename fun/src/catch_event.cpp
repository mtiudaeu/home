#include "module.h"
#include "log.h"

#include <SDL2/SDL.h>

static module_status catch_event_step(void*) {
  module_status step_status;
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      LOG_DEBUG("Quit event detected");
      step_status.info_code = module::STEP_INFO_STOPPING;
      return step_status;
    }
  }

  return step_status;
}

MODULE_EXPORT_API(0x0, 0x0, 0x0,
                  0x0, catch_event_step);
