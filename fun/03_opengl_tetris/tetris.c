#include "03_opengl_tetris/board.h"

#include "common/ui/ui_text.h"

#include "common/graphics/context.h"

#include "common/log/log.h"

#include <GL/glew.h>

#include <assert.h>

static UIText* internal_ui_text = 0x0;
GraphicsPoint2D internal_position = {0.1, 0.5};

//MDTMP
/*
static TetrisPiece* array_tetris_pieces[] = {0x0};
size_t array_tetris_pieces_size = 0;
*/



//--------------------------------------------------------------------------------
static void internal_handle_hotkey_cb(SDL_Event* ev) {
  assert(ev);
  if (ev->type == SDL_KEYDOWN) {
    switch (ev->key.keysym.sym) {
      case SDLK_LEFT:
        internal_position.x -= 0.1;
        break;
      case SDLK_RIGHT:
        internal_position.x += 0.1;
        break;
      case SDLK_UP:
        internal_position.y += 0.1;
        break;
      case SDLK_DOWN:
        internal_position.y -= 0.1;
        break;
    }
  }
  if (internal_ui_text) {
    ui_text_set_position(internal_ui_text, internal_position);
  }
}

//--------------------------------------------------------------------------------
static void internal_mainCallback() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  if (internal_ui_text) {
    ui_text_draw(internal_ui_text);
  }

  tetris_board_draw();

//MDTMP tetris_piece_draw(array_tetris_pieces, array_tetris_pieces_size);
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret = 0;
  { // initialization
    size_t ret = graphics_context_global_init();
    if (ret != 0) {
      return ret;
    }

    internal_ui_text = ui_text_calloc();
    if (!internal_ui_text) {
      LOG_ERROR("!internal_ui_text");
      return 1;
    }

    ui_text_set_scale(internal_ui_text, 1.0f);
    ui_text_set_position(internal_ui_text, internal_position);
    ui_text_set_msg(internal_ui_text, "test");

/*
    TetrisPiece* piece = tetris_piece_calloc();
    if (piece) {
      array_tetris_pieces[array_tetris_pieces_size++] = piece;
    }
*/
  }

  { // main loop
    ret = graphics_context_global_run(&internal_mainCallback,
                                      internal_handle_hotkey_cb);
    if (ret != 0) {
      LOG_ERROR("graphics_context_global_run");
      return ret;
    }
  }

  { // uninitialization
/*
    size_t i;
    for (i = 0; i < array_tetris_pieces_size; ++i) {
      tetris_piece_free(array_tetris_pieces[i]);
    }
*/

    ui_text_free(internal_ui_text);
    internal_ui_text = 0x0;

    ret = graphics_context_global_uninit();
    if (ret != 0) {
      LOG_ERROR("graphics_context_global_uninit");
    }
  }
  return ret;
}
