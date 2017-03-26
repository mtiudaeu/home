#include "module.h"
#include "log.h"

#include <GL/glew.h>

void* render_init_state(module_status&, void*, size_t) {
  return 0x0;
}

module_status render_uninit(void*)
{
  return module_status();
}

static module_status render_step(void*) {
  LOG_DEBUG("render_step");
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return module_status();
}

MODULE_EXPORT_API(render_init_state, render_uninit, 0x0,
                  0x0, render_step);
