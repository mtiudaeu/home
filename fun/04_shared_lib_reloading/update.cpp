#include "module.h"

#include "catch_event.h"
#include "global_data.h"

#include <assert.h>

struct update_state {
  struct catch_event* catch_event = 0x0;
  struct global_data* global_data = 0x0;
};

static void* update_init_state(module_status&, void** dependancies_state_array,
                               size_t dependancies_length) {
  assert(dependancies_state_array);
  assert(dependancies_length == 2);

  update_state* update_state = new struct update_state();
  update_state->catch_event =
      static_cast<struct catch_event*>(dependancies_state_array[0]);
  assert(update_state->catch_event);
  update_state->global_data =
      static_cast<struct global_data*>(dependancies_state_array[1]);
  assert(update_state->global_data);

  return update_state;
}

static module_status update_uninit(void* state) {
  assert(state);
  update_state* update_state = static_cast<struct update_state*>(state);
  delete update_state;
  update_state = 0x0;

  return module_status();
}

static module_status update_step(void* state) {
  assert(state);
  update_state* update_state = static_cast<struct update_state*>(state);
  assert(update_state->catch_event);
  assert(update_state->global_data);

  { // Catch keyboard events
    for (const SDL_Event ev : update_state->catch_event->event_queue) {
      if (ev.type == SDL_KEYDOWN) {
        switch (ev.key.keysym.sym) {
          case SDLK_LEFT:
            update_state->global_data->posx -= 1;
            break;
          case SDLK_RIGHT:
            update_state->global_data->posx += 1;
            break;
          case SDLK_UP:
            update_state->global_data->posy += 1;
            break;
          case SDLK_DOWN:
            update_state->global_data->posy -= 1;
            break;
        }
      }
    }
    update_state->catch_event->event_queue.clear();
  }
  { // Update time
    if (update_state->global_data->time_current == 0) {
      update_state->global_data->time_current = SDL_GetTicks();
    }

    const int time_new = SDL_GetTicks();
    update_state->global_data->time_delta =
        time_new - update_state->global_data->time_current;
    update_state->global_data->time_current = time_new;
  }

  return module_status();
}

MODULE_EXPORT_API(update_init_state, update_uninit, 0x0, 0x0, update_step);
