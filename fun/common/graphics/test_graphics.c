#include "test/test.h"

#include "graphics/context.h"
#include "graphics/text/text.h"

#include <GL/glew.h>

static GraphicsText* internal_graphics_text = 0x0;

//--------------------------------------------------------------------------------
static void internal_mainCallback() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (internal_graphics_text) {
    const float scale = 0.5f;
    const GraphicsPoint2D position = {0.1, 0.5};
    graphics_text_draw(internal_graphics_text, scale, position, "test");
  }
}

//--------------------------------------------------------------------------------
static size_t internal_test_integration()
{
  internal_graphics_text = graphics_text_from_tileset_calloc();

  const size_t ret = graphics_context_global_run(&internal_mainCallback);

  TEST_ASSERT_TRUE_PTR(internal_graphics_text);
  graphics_text_free(internal_graphics_text);
  internal_graphics_text = 0x0;

  return ret;
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret = graphics_context_global_init();
  TEST_ASSERT_MSG("graphics_context_global_init", ret);
  if (ret != 0) {
    return ret;
  }

  ret = graphics_text_run_test();
  TEST_ASSERT_MSG("graphics_text_run_test", ret);
  if (ret != 0) {
    return ret;
  }

  ret = internal_test_integration();
  TEST_ASSERT_MSG("internal_test_integration", ret);
  if (ret != 0) {
    return ret;
  }

  ret = graphics_context_global_uninit();
  TEST_ASSERT_MSG("graphics_context_global_uninit", ret);
  if (ret != 0) {
    return ret;
  }

  return ret;
}
