#include "sdl/context.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <memory>

struct Imp {
  ~Imp();

  SDL_Window* window = 0x0;
  SDL_GLContext sdl_context = 0x0;
};
static std::unique_ptr<Imp> imp;

Imp::~Imp() {
  if (sdl_context) {
    SDL_GL_DeleteContext(sdl_context);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }

  SDL_Quit();
}

Status sdl_context_init()
{
  imp.reset(new Imp());

  Status status;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    status = BUILD_ERROR("SDL_Init : %s", SDL_GetError());
    return status;
  }

  imp->window = SDL_CreateWindow(
      "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024,
      768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!imp->window) {
    status = BUILD_ERROR("SDL_CreateWindow %s", SDL_GetError());
    return status;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  imp->sdl_context = SDL_GL_CreateContext(imp->window);
  if (imp->sdl_context == NULL) {
    status = BUILD_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
    return status;
  }

  // FIXME validate if glewInit this need clean-up.
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    status = BUILD_ERROR("glewInit %s", glewGetErrorString(glew_status));
    return status;
  }
  if (!GLEW_VERSION_2_0) {
    status = BUILD_ERROR("graphic card does not support OpenGL 2.0");
    return status;
  }

  return status;

}

Status sdl_context_swap_buffer() {
  if( !imp )
  {
    return BUILD_ERROR("!imp");
  }

  SDL_GL_SwapWindow(imp->window);

  return Status();
}

Status sdl_context_catch_event() {
  Status status;
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      LOG_DEBUG("Quit event detected");
      status = BUILD_STATUS(Status::QUIT_EVENT);
      return status;
    }
//MDTMP Save hotkey everywhere to consume later.
/*
    if (ev.type == SDL_KEYDOWN) {
      game_data_s* game_data = DM_GET_DATA(*data_manager, game_data_s, "game");
      assert(game_data);
      std::map<std::string, int>& data = game_data->data;
      switch (ev.key.keysym.sym) {
        case SDLK_LEFT:
          data["posx"] -= 1;
          break;
        case SDLK_RIGHT:
          data["posx"] += 1;
          break;
        case SDLK_UP:
          data["posy"] += 1;
          break;
        case SDLK_DOWN:
          data["posy"] -= 1;
          break;
      }
    }
*/
  }

  return status;
}

