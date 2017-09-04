#include "app.h"

#include "sdl/context.h"

#include "gl/render.h"
#include "gl/render_2d_texture.h"
#include "gl/text.h"


namespace {

Status init() {
  Status status = sdl_context_init();
  if(!status){ return status; }

  status = gl_render_2d_init();
  if(!status){ return status; }

  status = gl_text_init();
  return status;
}

Status step() {

  Status status = sdl_context_catch_event();
  if (status.getId() == Status::QUIT_EVENT) {
    return status;
  }
  if (!status) { return status; }

  status = gl_render();
  if (!status) { return status; }

  status = gl_render_2d();
  if (!status) { return status; }

  status = sdl_context_swap_buffer();
  if (!status) { return status; }
}

}

int main() {
  Status status = init();
  if (!status) {
    LOG_ERROR(status);
    return 1;
  }

  while (1) {
    Status status = step();
    if (status.getId() == Status::QUIT_EVENT) {
      LOG_DEBUG("Quit event detected, stop main loop.");
      return 0;
    }
    if (!status) {
      LOG_ERROR(status);
      return 1;
    }
  }

  return 0;
}
