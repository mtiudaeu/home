#include <App.h>

#include <sdl/SDLWrapper.h>

#include <macros.h>

#include <SDL2/SDL_events.h>

#include <iostream>

struct App::Imp {
  SDLWrapper m_sdlWrapper;
};

App::App() : m_imp(new App::Imp()) {}

App::~App() {
  delete m_imp;
  m_imp = nullptr;
}

int App::run() noexcept {
  assert(m_imp);

  try {
    while (1) {
      m_imp->m_sdlWrapper.swapBuffer();
      m_imp->m_sdlWrapper.catch_quit_event();
    }
  } catch (const std::exception& e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}
