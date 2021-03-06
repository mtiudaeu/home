#include "core/log.h"
#include "core/module.h"

#include "game/global_data.h"

#include <GL/glew.h>

#include <assert.h>

struct render_state {
  struct global_data* global_data = 0x0;
};

static void* render_init_state(module_status&, void** dependencies_state_array,
                        size_t dependencies_length) {
  assert(dependencies_state_array);
  assert(dependencies_length == 1);

  render_state* render_state = new struct render_state();
  render_state->global_data =
      static_cast<struct global_data*>(dependencies_state_array[0]);
  assert(render_state->global_data);

  return render_state;
}

static module_status render_uninit(void* state)
{
  assert(state);
  render_state* render_state = static_cast<struct render_state*>(state);
  delete render_state;
  render_state = 0x0;

  return module_status();
}

static module_status render_step(void* state) {
  assert(state);
  render_state* render_state = static_cast<struct render_state*>(state);
  assert(render_state->global_data);

  LOG_DEBUG("time_current %d", render_state->global_data->time_current);
  LOG_DEBUG("time_delta %d", render_state->global_data->time_delta);
  LOG_DEBUG("posx %d", render_state->global_data->posx);
  LOG_DEBUG("posy %d", render_state->global_data->posy);

  LOG_DEBUG("render_step");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return module_status();
}

MODULE_EXPORT_API(render_init_state, render_uninit, 0x0,
                  0x0, render_step);
