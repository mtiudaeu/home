#include <sdl/SDLWrapper.h>

#include <macros.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

struct SDLWrapper::Imp {
  SDL_Window *window = 0x0;
  SDL_GLContext sdl_context = 0x0;
};

SDLWrapper::SDLWrapper() :
m_imp(new Imp)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    THROW_ERR("SDL_Init : " + SDL_GetError());
  }

  m_imp->window = SDL_CreateWindow("Default Parameter", SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED, 1024, 768,
                                 SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!m_imp->window) {
    THROW_ERR("SDL_CreateWindow : " + SDL_GetError());
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  m_imp->sdl_context = SDL_GL_CreateContext(m_imp->window);
  if (!m_imp->sdl_context) {
    THROW_ERR("SDL_GL_CreateContext : " + SDL_GetError());
  }

  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    THROW_ERR("glewInit : " + std::to_string(glew_status));
  }
  if (!GLEW_VERSION_2_0) {
    THROW_ERR("graphic card does not support OpenGL 2.0");
  }
}

SDLWrapper::~SDLWrapper()
{
  assert(m_imp->sdl_context);
  SDL_GL_DeleteContext(m_imp->sdl_context);

  assert(m_imp->window);
  SDL_DestroyWindow(m_imp->window);

  SDL_Quit();

  delete m_imp;
  m_imp = nullptr;
}

void SDLWrapper::swapBuffer() const {
  assert(m_imp);
  SDL_GL_SwapWindow(m_imp->window);
}

void SDLWrapper::catch_quit_event() const {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
//FIXME throw custom exception instead.
      THROW_ERR("Detected quit event");
    }
  }
}
