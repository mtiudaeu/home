#include "gl/render.h"

#include <GL/glew.h>

Status gl_render() {
  LOG_DEBUG("gl_render");

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  return Status();
}
