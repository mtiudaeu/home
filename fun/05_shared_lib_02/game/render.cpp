#include "core/log.h"
#include "core/module_create.h"

#include <GL/glew.h>

#include <map>
#include <string>

MODULE_DEFAULT_INITIALIZE;

static status_s render_step_cb() {
  assert(data_manager);

  std::map<std::string, int>* data_ptr = static_cast<std::map<std::string, int>*>(
    data_manager->get_data(data_manager_s::ID_DATA));
  assert(data_ptr);
  std::map<std::string, int>& data = *data_ptr;

  LOG_DEBUG("time_current %d", data["time_current"]);
  LOG_DEBUG("time_delta %d", data["time_delta"]);
  LOG_DEBUG("posx %d", data["posx"]);
  LOG_DEBUG("posy %d", data["posy"]);

  LOG_DEBUG("render_step_cb");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return status_s();
}

MODULE_EXPORT_STEP_CB(render_step_cb);
