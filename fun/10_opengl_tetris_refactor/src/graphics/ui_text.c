#include <graphics/ui_text.h>

#include "graphics/primitive_text.h"

#include "common/log/log.h"

#include "common/test/test.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------
struct graphics_ui_text {
  struct graphics_text* graphics_text;
  struct graphics_coord_2d position;
  float scale;
  char* msg;
};

//--------------------------------------------------------------------------------
struct graphics_ui_text* graphics_ui_text_new() {
  struct graphics_ui_text* graphics_ui_text = calloc(1, sizeof(struct graphics_ui_text));
  graphics_ui_text->graphics_text = graphics_text_new();
  if (!graphics_ui_text->graphics_text) {
    LOG_ERROR("!graphics_ui_text->graphics_text");
    return 0x0;
  }
  graphics_ui_text->scale = 1.0f;

  return graphics_ui_text;
}

//--------------------------------------------------------------------------------
void graphics_ui_text_delete(struct graphics_ui_text* graphics_ui_text) {
  assert(graphics_ui_text);
  graphics_text_delete(graphics_ui_text->graphics_text);
  if (graphics_ui_text->msg) {
    free(graphics_ui_text->msg);
  }
  free(graphics_ui_text);
}

//--------------------------------------------------------------------------------
void graphics_ui_text_set_scale(struct graphics_ui_text* graphics_ui_text, float scale) {
  assert(graphics_ui_text);
  graphics_ui_text->scale = scale;
}

//--------------------------------------------------------------------------------
void graphics_ui_text_set_position(struct graphics_ui_text* graphics_ui_text, struct graphics_coord_2d position) {
  assert(graphics_ui_text);
  graphics_ui_text->position = position;
}

//--------------------------------------------------------------------------------
void graphics_ui_text_set_msg(struct graphics_ui_text* graphics_ui_text, const char* msg) {
  if (!msg) {
    LOG_ERROR("!msg");
    return;
  }
  assert(graphics_ui_text);

  if (graphics_ui_text->msg) {
    free(graphics_ui_text->msg);
  }
  graphics_ui_text->msg = malloc(strlen(msg) + 1);
  strcpy(graphics_ui_text->msg, msg);
}

//--------------------------------------------------------------------------------
void graphics_ui_text_draw(const struct graphics_ui_text* graphics_ui_text) {
  assert(graphics_ui_text);

  if (!graphics_ui_text->msg) {
    return;
  }
  graphics_text_draw(graphics_ui_text->graphics_text, graphics_ui_text->scale, graphics_ui_text->position,
                     graphics_ui_text->msg);
}

#ifdef INCLUDE_RUN_TEST
static struct graphics_ui_text* test_graphics_ui_text = 0x0;

//--------------------------------------------------------------------------------
size_t test_graphics_ui_text_init()
{
  test_graphics_ui_text = graphics_ui_text_new();
  assert(test_graphics_ui_text );

  graphics_ui_text_set_scale(test_graphics_ui_text, 1.2f);
  struct graphics_coord_2d position = {-0.8f, 0.2};
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
#endif // INCLUDE_RUN_TEST

