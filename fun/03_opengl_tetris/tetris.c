#include "common/graphics/context.h"
#include "common/graphics/text/text.h"

#include "common/log.h"

#include <GL/glew.h>

#include <assert.h>

static GraphicsText* internal_graphics_text = 0x0;
//MDTMP
GraphicsPoint2D position = {0.1, 0.5};

//--------------------------------------------------------------------------------
static void internal_mainCallback(SDL_Event* ev) {
  assert(ev);
//MDTMP
  if (ev->type == SDL_KEYDOWN) {
    position.x -= 0.1;
  }
  else if (ev->type == SDL_KEYUP) {
    position.x += 0.1;
  }

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (internal_graphics_text) {
    const float scale = 0.5f;
    graphics_text_draw(internal_graphics_text, scale, position, "test");
  }
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret = graphics_context_global_init();
  if (ret != 0) {
    return ret;
  }

  internal_graphics_text = graphics_text_from_tileset_calloc();

  ret = graphics_context_global_run(&internal_mainCallback);
  if (ret != 0) {
    LOG_ERROR("graphics_context_global_run");
    return ret;
  }

  graphics_text_free(internal_graphics_text);
  internal_graphics_text = 0x0;

  ret = graphics_context_global_uninit();
  if (ret != 0) {
    LOG_ERROR("graphics_context_global_uninit");
  }

  return ret;
}
