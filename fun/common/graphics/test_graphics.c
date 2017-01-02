#include "test/test.h"

#include "graphics/context.h"
#include "graphics/text.h"

#include <GL/glew.h>

//MDTMP remove from static
static GraphicsText* graphics_text = 0x0;

//--------------------------------------------------------------------------------
void mainCallback() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (graphics_text) {
    graphics_text_draw(graphics_text, "test");
  }

}

//--------------------------------------------------------------------------------
static size_t internal_test_integration()
{
  graphics_text = graphics_text_from_tileset_malloc(
      "test/assets/ASCII_tileset.png");

  const size_t ret = graphics_context_global_run(&mainCallback);

  TEST_ASSERT_TRUE_PTR(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

  return ret;
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret;
  //MDTMP
/*
  size_t ret = graphics_context_run_test();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_context_run_test");
    return ret;
  }
*/

  graphics_context_global_init();

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

  graphics_context_global_uninit();

  return ret;
}
