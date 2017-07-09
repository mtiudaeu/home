#include "gl/shader.h"

#include "core/module_create.h"

#include <GL/glew.h>

#include <map>
#include <string>

MODULE_DEFAULT_INITIALIZE;

#include "gl/text.private_2.h"
#include "gl/text.private_3.h"

static status_s render_step_cb() {
  assert(data_manager);

  func2();
  func3();

  return status_s();
}

MODULE_EXPORT_STEP_CB(render_step_cb);
