#include "common/test/test.h"

#include "common/ui/ui_text.h"

#include "common/graphics/context.h"
#include "common/graphics/text/text.h"

#include "common/graphics/primitive/rectangle_2D.h"

#include <GL/glew.h>

//--------------------------------------------------------------------------------
// static members
#define CALLBACKS_MAX_SIZE 100
size_t callbacks_size = 0;

//MDTMP remove all of that!!
typedef void (*DrawCallback)(void);
DrawCallback draw_callbacks[CALLBACKS_MAX_SIZE];
typedef void (*UninitCallback)(void);
DrawCallback uninit_callbacks[CALLBACKS_MAX_SIZE];

//--------------------------------------------------------------------------------
static void run_test_mainCallback(const float time_delta) {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  { // draw all test sub modules.
    test_graphics_text_draw();
    test_graphics_primitive_rectangle_2D_draw();
    test_ui_text_draw();
  }
}

//--------------------------------------------------------------------------------
static size_t run_test_draw()
{
  // drawing main loop
  const size_t ret = graphics_context_global_run(&run_test_mainCallback,
                                                 0x0  // handle_hotkey_cb
                                                 );
  return ret;
}

//--------------------------------------------------------------------------------
static size_t run_test_sub_modules()
{
  size_t ret= 0;
  { // graphics_text_text
    ret = test_graphics_text_run();
    if (ret != 0) {
      TEST_ASSERT_MSG("test_graphics_text_run");
      return ret;
    }
  }

  { // test_graphics_primitive_rectangle_2D
    ret = test_graphics_primitive_rectangle_2D_run();
    if (ret != 0) {
      TEST_ASSERT_MSG("test_graphics_primitive_rectangle_2D_run");
      return ret;
    }
  }

  { // ui_text
    ret = test_ui_text_run();
    if (ret != 0) {
      TEST_ASSERT_MSG("test_ui_text_run");
      return ret;
    }
  }
  return ret;
}

//--------------------------------------------------------------------------------
static size_t run_test_init()
{
  size_t ret = graphics_context_global_init();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_context_global_init");
    return ret;
  }

  ret = test_graphics_text_init();
  if (ret != 0) {
    TEST_ASSERT_MSG("test_graphics_text_init");
    return ret;
  }
  ret = test_graphics_primitive_rectangle_2D_init();
  if (ret != 0) {
    TEST_ASSERT_MSG("test_graphics_primitive_rectangle_2D_init");
    return ret;
  }
  ret = test_ui_text_init();
  if (ret != 0) {
    TEST_ASSERT_MSG("test_ui_text_init");
    return ret;
  }

  return ret;
}

//--------------------------------------------------------------------------------
static size_t run_test_uninit()
{
  size_t ret = graphics_context_global_uninit();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_context_global_uninit");
    return ret;
  }

  ret = test_graphics_text_uninit();
  if (ret != 0) {
    TEST_ASSERT_MSG("test_graphics_text_uninit");
    return ret;
  }
  ret = test_graphics_primitive_rectangle_2D_uninit();
  if (ret != 0) {
    TEST_ASSERT_MSG("test_graphics_primitive_rectangle_2D_uninit");
    return ret;
  }
  ret = test_ui_text_uninit();
  if (ret != 0) {
    TEST_ASSERT_MSG("test_ui_text_uninit");
    return ret;
  }
  return ret;
}


//--------------------------------------------------------------------------------
int main() {

  size_t ret = run_test_init();
  if (ret != 0) {
    return ret;
  }

  ret = run_test_sub_modules();
  if (ret != 0) {
    TEST_ASSERT_MSG("run_test_sub_modules");
    return ret;
  }

  ret = run_test_draw();
  if (ret != 0) {
    TEST_ASSERT_MSG("run_test_draw");
    return ret;
  }

  ret = run_test_uninit();
  if (ret != 0) {
    return ret;
  }


  return ret;
}
