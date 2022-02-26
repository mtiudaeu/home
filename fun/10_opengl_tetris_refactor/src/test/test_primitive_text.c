#include "graphics/primitive_text.h"
#include "graphics/primitive_text.private.h"

#include "common/test.h"

static struct graphics_text* graphics_text_graphics_text = 0x0;

//--------------------------------------------------------------------------------
size_t test_graphics_text_init() {
  graphics_text_graphics_text = graphics_text_new();
  assert(graphics_text_graphics_text);
  return 0;
}

//--------------------------------------------------------------------------------
size_t test_graphics_text_uninit() {
  assert(graphics_text_graphics_text);
  graphics_text_delete(graphics_text_graphics_text);
  graphics_text_graphics_text = 0x0;
  return 0;
}

//--------------------------------------------------------------------------------
void test_graphics_text_draw() {
  assert(graphics_text_graphics_text);
  const float scale = 1.0f;
  const struct math_vec2 position = {0.1, 0.5};
  graphics_text_draw(graphics_text_graphics_text, scale, position, "test");
}

//--------------------------------------------------------------------------------
size_t test_graphics_text_run() {
  {  // Test _graphics_text_char_to_grid_coord
    struct grid_16x16 coord = _graphics_text_char_to_grid_coord((char)0);
    TEST_ASSERT_TRUE(coord.x == 0);
    TEST_ASSERT_TRUE(coord.y == 0);

    coord = _graphics_text_char_to_grid_coord((char)16);
    TEST_ASSERT_TRUE(coord.x == 0);
    TEST_ASSERT_TRUE(coord.y == 1);

    // Overflow
    coord = _graphics_text_char_to_grid_coord((char)256);
    TEST_ASSERT_TRUE(coord.x == 0);
    TEST_ASSERT_TRUE(coord.y == 0);

    coord = _graphics_text_char_to_grid_coord((char)34);
    TEST_ASSERT_TRUE(coord.x == 2);
    TEST_ASSERT_TRUE(coord.y == 2);
  }

  return 0;
}

