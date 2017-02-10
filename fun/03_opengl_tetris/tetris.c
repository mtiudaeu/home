#include "03_opengl_tetris/board.h"

#include "common/ui/ui_text.h"

#include "common/graphics/primitive/rectangle_2D.h"
#include "common/graphics/context.h"

#include "common/log/log.h"

#include <GL/glew.h>

#include <assert.h>

//--------------------------------------------------------------------------------
// static members
static UIText* internal_ui_text = 0x0;
static float time_until_last_update = 0.0f;

//--------------------------------------------------------------------------------
// private methods
static size_t tetris_init();
static void tetris_uninit();
static void tetris_handle_hotkey_cb(SDL_Event* ev);
static void tetris_mainCallback(const float time_delta);
int main();

//--------------------------------------------------------------------------------
static size_t tetris_init()
{
  { // initialize static modules
    size_t ret = graphics_context_global_init();
    if (ret != 0) {
      LOG_ERROR("graphics_context_global_init");
      return ret;
    }

    ret = graphics_primitive_rectangle_2D_init();
    if (ret != 0) {
      LOG_ERROR("graphics_primitive_rectangle_2D_init");
      return ret;
    }

    ret = tetris_board_init();
    if (ret != 0) {
      LOG_ERROR("tetris_board_init");
      return ret;
    }
  }

  {  // initialize tetris members
    internal_ui_text = ui_text_calloc();
    if (!internal_ui_text) {
      LOG_ERROR("!internal_ui_text");
      return 1;
    }

    ui_text_set_scale(internal_ui_text, 1.0f);
    const GraphicsPoint2D internal_position = {0.1, 0.5};
    ui_text_set_position(internal_ui_text, internal_position);
    ui_text_set_msg(internal_ui_text, "test");
  }
  return 0;
}

//--------------------------------------------------------------------------------
static void tetris_uninit()
{
  {  // uninitialize tetris members
    ui_text_free(internal_ui_text);
    internal_ui_text = 0x0;
  }

  { // uninitialize static modules
    tetris_board_uninit();

    graphics_primitive_rectangle_2D_uninit();

    size_t ret = graphics_context_global_uninit();
    if (ret != 0) {
      LOG_ERROR("graphics_context_global_uninit");
    }
  }
}

//--------------------------------------------------------------------------------
static void tetris_handle_hotkey_cb(SDL_Event* ev) {
  assert(ev);
  if (ev->type == SDL_KEYDOWN) {
    switch (ev->key.keysym.sym) {
      case SDLK_LEFT:
        tetris_board_send_command( BOARD_CMD_MOV_LEFT );
        break;
      case SDLK_RIGHT:
        tetris_board_send_command( BOARD_CMD_MOV_RIGHT );
        break;
      case SDLK_UP:
        tetris_board_send_command( BOARD_CMD_ROT );
        break;
      case SDLK_DOWN:
        tetris_board_send_command( BOARD_CMD_MOV_DOWN );
        break;
    }
  }
}

//--------------------------------------------------------------------------------
static void tetris_mainCallback(const float time_delta) {
  time_until_last_update += time_delta;
  const float time_update_frequency = 1.0f;
  if ( time_until_last_update >= time_update_frequency ) {
    time_until_last_update -= time_update_frequency;
    tetris_board_update();
  }

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  assert(internal_ui_text);
  ui_text_draw(internal_ui_text);

  tetris_board_draw();
}

//--------------------------------------------------------------------------------
int main() {
  { // init
    size_t ret = tetris_init();
    assert(ret == 0);
  }

  { // main loop
    size_t ret = graphics_context_global_run(&tetris_mainCallback,
                                             tetris_handle_hotkey_cb);
    assert(ret == 0);
  }

  { // uninit
    tetris_uninit();
  }

  return 0;
}
