#include "test/test.h"

#include "graphics/context.h"
#include "graphics/text.h"

//--------------------------------------------------------------------------------
static size_t internal_test_integration()
{
  // MDTMP
  /*
    GraphicsText* graphics_text = graphics_text_from_tileset_malloc(
        "test/assets/Cooz_curses_square_16x16.png");

    TEST_ASSERT_TRUE(graphics_text);
    graphics_text_free(graphics_text);
    graphics_text = 0x0;
  */
  graphics_context_global_init();
  graphics_context_global_uninit();

  return 0;
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret = internal_test_integration();
  TEST_ASSERT_TRUE_SIZE_T(ret == 0);

  ret = graphics_text_test_run();
  TEST_ASSERT_TRUE_SIZE_T(ret == 0);

  return ret;
}
