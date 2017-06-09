#include "core/log.h"
#include "core/module.h"
#include "core/data_manager.h"

#include "game/global_data.h"

#include <GL/glew.h>

#include <assert.h>

struct render_state {
  struct global_data* global_data = 0x0;
};
static data_manager_s* data_manager = 0x0;

static status_s render_init_cb(data_manager_s* data) {
  data_manager = data;
  assert(data_manager);
  return status_s();
}

static status_s render_uninit_cb() {
  assert(data_manager);
  data_manager = 0x0;
  return status_s();
}

static status_s render_step_cb() {
  assert(data_manager);

//MDTMP LOG_DEBUG("time_current %d", data_manager->MDTMP_data["time_current"]);
//MDTMP LOG_DEBUG("time_delta %d", data_manager->MDTMP_data["time_delta"]);
  LOG_DEBUG("posx %d", data_manager->MDTMP_data["posx"]);
  LOG_DEBUG("posy %d", data_manager->MDTMP_data["posy"]);

  LOG_DEBUG("render_step_cb");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return status_s();
}

MODULE_EXPORT (render_init_cb, render_uninit_cb, render_step_cb);
