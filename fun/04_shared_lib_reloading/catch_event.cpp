#include "catch_event.h"

#include "core/log.h"
#include "core/module.h"

#include <assert.h>

static void* catch_event_init_state(module_status&, void**, size_t) {
  return new struct catch_event();
}

static module_status catch_event_uninit(void* state)
{
  assert(state);
  catch_event* catch_event = static_cast<struct catch_event*>(state);
  delete catch_event;

  return module_status();
}

static module_status catch_event_step(void* state) {
  assert(state);
  catch_event* catch_event = static_cast<struct catch_event*>(state);

  module_status step_status;
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      LOG_DEBUG("Quit event detected");
      step_status.info_code = module::STEP_INFO_STOPPING;
      return step_status;
    }
    catch_event->event_queue.push_back(ev);
  }

  return step_status;
}

MODULE_EXPORT_API(catch_event_init_state, catch_event_uninit, 0x0,
                  0x0, catch_event_step);
