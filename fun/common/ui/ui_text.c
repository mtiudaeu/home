#include <common/ui/ui_text.h>

#include "common/graphics/text/text.h"

#include "common/log/log.h"

#include "common/test/test.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------
struct UIText {
  GraphicsText* graphics_text;
  GraphicsPoint2D position;
  float scale;
  char* msg;
};

//--------------------------------------------------------------------------------
UIText* ui_text_calloc() {
  UIText* ui_text = calloc(1, sizeof(UIText));
  ui_text->graphics_text = graphics_text_calloc();
  if (!ui_text->graphics_text) {
    LOG_ERROR("!ui_text->graphics_text");
    return 0x0;
  }
  ui_text->scale = 1.0f;

  return ui_text;
}

//--------------------------------------------------------------------------------
void ui_text_free(UIText* ui_text) {
  assert(ui_text);
  graphics_text_free(ui_text->graphics_text);
  if (ui_text->msg) {
    free(ui_text->msg);
  }
  free(ui_text);
}

//--------------------------------------------------------------------------------
void ui_text_set_scale(UIText* ui_text, float scale) {
  assert(ui_text);
  ui_text->scale = scale;
}

//--------------------------------------------------------------------------------
void ui_text_set_position(UIText* ui_text, GraphicsPoint2D position) {
  assert(ui_text);
  ui_text->position = position;
}

//--------------------------------------------------------------------------------
void ui_text_set_msg(UIText* ui_text, const char* msg) {
  if (!msg) {
    LOG_ERROR("!msg");
    return;
  }
  assert(ui_text);

  if (ui_text->msg) {
    free(ui_text->msg);
  }
  ui_text->msg = malloc(strlen(msg) + 1);
  strcpy(ui_text->msg, msg);
}

//--------------------------------------------------------------------------------
void ui_text_draw(const UIText* ui_text) {
  assert(ui_text);

  if (!ui_text->msg) {
    return;
  }
  graphics_text_draw(ui_text->graphics_text, ui_text->scale, ui_text->position,
                     ui_text->msg);
}

#ifdef INCLUDE_RUN_TEST
static UIText* test_ui_text = 0x0;

//--------------------------------------------------------------------------------
static void test_ui_test_draw_callback()
{
  if (!test_ui_text) {
    test_ui_text = ui_text_calloc();
    assert(test_ui_text );

    ui_text_set_scale(test_ui_text, 1.2f);
    GraphicsPoint2D position = {-0.8f, 0.2};
    ui_text_set_position(test_ui_text, position);
    ui_text_set_msg(test_ui_text, "ui_test_ whoo!");
  } else {
    ui_text_draw(test_ui_text);
  }
}

//--------------------------------------------------------------------------------
static void test_ui_test_uninit_callback()
{
  assert(test_ui_text);
  ui_text_free(test_ui_text);
  test_ui_text = 0x0;
}

//--------------------------------------------------------------------------------
size_t ui_text_run_test(void (** draw_callback)(void),
                        void (** uninit_callback)(void))
{
  {  // Set draw and uninit callback
    if (!draw_callback) {
      TEST_ASSERT_MSG("!draw_callback");
      return 1;
    }
    if (!uninit_callback) {
      TEST_ASSERT_MSG("!uninit_callback");
      return 1;
    }
    *draw_callback = &test_ui_test_draw_callback;
    *uninit_callback = &test_ui_test_uninit_callback;
  }

  return 0;
}
#endif // INCLUDE_RUN_TEST

