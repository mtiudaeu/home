#include "core/log.h"
#include "core/module.h"
#include "core/data_manager.h"

#include <GL/glew.h>

#include <assert.h>

MODULE_DEFAULT_INITIALIZE;

static status_s render_step_cb() {
  assert(data_manager);

  LOG_DEBUG("time_current %d", data_manager->MDTMP_data["time_current"]);
  LOG_DEBUG("time_delta %d", data_manager->MDTMP_data["time_delta"]);
  LOG_DEBUG("posx %d", data_manager->MDTMP_data["posx"]);
  LOG_DEBUG("posy %d", data_manager->MDTMP_data["posy"]);

  LOG_DEBUG("render_step_cb");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return status_s();
}

MODULE_EXPORT_STEP_CB(render_step_cb);
