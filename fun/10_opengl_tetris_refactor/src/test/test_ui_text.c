#include "test/test_ui_text.h"

#include "graphics/ui_text.h"

#include <assert.h>

static struct graphics_ui_text* test_graphics_ui_text = 0x0;

//--------------------------------------------------------------------------------
size_t test_graphics_ui_text_init()
{
  test_graphics_ui_text = graphics_ui_text_new();
  assert(test_graphics_ui_text );

  graphics_ui_text_set_scale(test_graphics_ui_text, 1.2f);
  struct math_vec2 position = {-0.8f, 0.2};
  graphics_ui_text_set_position(test_graphics_ui_text, position);
  graphics_ui_text_set_msg(test_graphics_ui_text, "ui_test_ whoo!");

  return 0;
}

//--------------------------------------------------------------------------------
size_t test_graphics_ui_text_uninit()
{
  assert(test_graphics_ui_text);
  graphics_ui_text_delete(test_graphics_ui_text);
  test_graphics_ui_text = 0x0;

  return 0;
}

//--------------------------------------------------------------------------------
void test_graphics_ui_text_draw()
{
  assert(test_graphics_ui_text);
  graphics_ui_text_draw(test_graphics_ui_text);
}

//--------------------------------------------------------------------------------
size_t test_graphics_ui_text_run()
{
  return 0;
}

