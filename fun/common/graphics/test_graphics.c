#include "common/test/test.h"

#include "common/graphics/context.h"
#include "common/graphics/text/text.h"

#include "common/graphics/primitive/rectangle_2D.h"

#include <GL/glew.h>

#define CALLBACKS_MAX_SIZE 100
size_t callbacks_size = 0;

typedef void (*DrawCallback)(void);
DrawCallback draw_callbacks[CALLBACKS_MAX_SIZE];
typedef void (*UninitCallback)(void);
DrawCallback uninit_callbacks[CALLBACKS_MAX_SIZE];

//--------------------------------------------------------------------------------
static void internal_mainCallback() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  size_t i = 0;
  for (; i < callbacks_size; ++i) {
    draw_callbacks[i]();
  }
}

//--------------------------------------------------------------------------------
static size_t internal_test_integration_draw()
{
  const size_t ret = graphics_context_global_run(&internal_mainCallback,
                                                 0x0  // handle_hotkey_cb
                                                 );
  size_t i = 0;
  for (; i < callbacks_size; ++i) {
    uninit_callbacks[i]();
  }

  return ret;
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret = graphics_context_global_init();
  TEST_ASSERT_MSG("graphics_context_global_init", ret);
  if (ret != 0) {
    return ret;
  }

  DrawCallback draw_callback = 0x0;
  UninitCallback uninit_callback = 0x0;
  { // graphics_text
    ret = graphics_text_run_test(&draw_callback, &uninit_callback);
    TEST_ASSERT_MSG("graphics_text_run_test", ret);
    if (ret != 0) {
      return ret;
    }
    draw_callbacks[callbacks_size] = draw_callback;
    uninit_callbacks[callbacks_size] = uninit_callback;
    callbacks_size++;
    draw_callback = 0x0;
    uninit_callback = 0x0;
  }

  { // graphics_primitive_rectangle_2D
    ret = graphics_primitive_rectangle_2D_run_test(&draw_callback, &uninit_callback);
    TEST_ASSERT_MSG("graphics_primitive_rectangle_2D_run_test", ret);
    if (ret != 0) {
      return ret;
    }
    draw_callbacks[callbacks_size] = draw_callback;
    uninit_callbacks[callbacks_size] = uninit_callback;
    callbacks_size++;
    draw_callback = 0x0;
    uninit_callback = 0x0;
  }

  ret = internal_test_integration_draw();
  TEST_ASSERT_MSG("internal_test_integration_draw", ret);
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
