#include "core/data/runtime_data.h"

#include "core/module_create.h"

#include <GL/glew.h>

MODULE_DEFAULT_INITIALIZE;

static status_s render_step_cb() {
  assert(data_manager);

  runtime_data_s* runtime_data = static_cast<runtime_data_s*>(
    data_manager->get_data(DSI_RUNTIME));
  assert(runtime_data);
  auto& data = runtime_data->data;

  LOG_DEBUG("time_current %s", data["time_current"].c_str());
  LOG_DEBUG("time_delta %s", data["time_delta"].c_str());
  LOG_DEBUG("posx %s", data["posx"].c_str());
  LOG_DEBUG("posy %s", data["posy"].c_str());

  LOG_DEBUG("render_step_cb");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return status_s();
}

MODULE_EXPORT_STEP_CB(render_step_cb);
