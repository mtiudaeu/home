#include <common/ui/ui_text.h>

#include "graphics/text/text.h"

#include "common/log/log.h"

#include "common/test/test.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------
struct ui_text {
  struct graphics_text* graphics_text;
  struct graphics_coord_2d position;
  float scale;
  char* msg;
};

//--------------------------------------------------------------------------------
struct ui_text* ui_text_new() {
  struct ui_text* ui_text = calloc(1, sizeof(struct ui_text));
  ui_text->graphics_text = graphics_text_new();
  if (!ui_text->graphics_text) {
    LOG_ERROR("!ui_text->graphics_text");
    return 0x0;
  }
  ui_text->scale = 1.0f;

  return ui_text;
}

//--------------------------------------------------------------------------------
void ui_text_delete(struct ui_text* ui_text) {
  assert(ui_text);
  graphics_text_delete(ui_text->graphics_text);
  if (ui_text->msg) {
    free(ui_text->msg);
  }
  free(ui_text);
}

//--------------------------------------------------------------------------------
void ui_text_set_scale(struct ui_text* ui_text, float scale) {
  assert(ui_text);
  ui_text->scale = scale;
}

//--------------------------------------------------------------------------------
void ui_text_set_position(struct ui_text* ui_text, struct graphics_coord_2d position) {
  assert(ui_text);
  ui_text->position = position;
}

//--------------------------------------------------------------------------------
void ui_text_set_msg(struct ui_text* ui_text, const char* msg) {
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
void ui_text_draw(const struct ui_text* ui_text) {
  assert(ui_text);

  if (!ui_text->msg) {
    return;
  }
  graphics_text_draw(ui_text->graphics_text, ui_text->scale, ui_text->position,
                     ui_text->msg);
}

#ifdef INCLUDE_RUN_TEST
static struct ui_text* test_ui_text = 0x0;

//--------------------------------------------------------------------------------
size_t test_ui_text_init()
{
  test_ui_text = ui_text_new();
  assert(test_ui_text );

  ui_text_set_scale(test_ui_text, 1.2f);
  struct graphics_coord_2d position = {-0.8f, 0.2};
  ui_text_set_position(test_ui_text, position);
  ui_text_set_msg(test_ui_text, "ui_test_ whoo!");

  return 0;
}

//--------------------------------------------------------------------------------
size_t test_ui_text_uninit()
{
  assert(test_ui_text);
  ui_text_delete(test_ui_text);
  test_ui_text = 0x0;

  return 0;
}

//--------------------------------------------------------------------------------
void test_ui_text_draw()
{
  assert(test_ui_text);
  ui_text_draw(test_ui_text);
}

//--------------------------------------------------------------------------------
size_t test_ui_text_run()
{
  return 0;
}
#endif // INCLUDE_RUN_TEST

