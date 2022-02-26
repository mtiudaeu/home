#include "tetris/board.h"

#include "graphics/primitive_rectangle_2D.h"
#include "graphics/context.h"

#include "common/log.h"

#include <GL/glew.h>

#include <assert.h>

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

  return 0;
}

//--------------------------------------------------------------------------------
static void tetris_uninit()
{
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
  tetris_board_update(time_delta);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

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
