#include <SDL.h>
#include <SDL_opengl.h>

#include "common.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static bool main_loop_running = true;
static SDL_Window* window;
static int width, height;
static int FRAME;
static bool visible = true;

static void HandleResize() {
  SDL_GL_GetDrawableSize(window, &width, &height);
  glViewport(0, 0, width, height);
}

void main_loop() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        main_loop_running = false;
        break;
      }
      case SDL_KEYUP: {
        int sym = event.key.keysym.sym;
        if (sym == SDLK_ESCAPE) {
          main_loop_running = false;
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        LOG("Mouse have been cliked mdtmp!");
        SDL_MouseButtonEvent& mouse_event = event.button;
        LOG("x:%d,y:%d", mouse_event.x, mouse_event.y);
        break;
      }
      case SDL_WINDOWEVENT_SHOWN: {
        visible = true;
        break;
      }
      case SDL_WINDOWEVENT_HIDDEN: {
        visible = false;
        break;
      }
      case SDL_WINDOWEVENT_SIZE_CHANGED: {
        HandleResize();
        break;
      }
    }
  }

  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
}

int main(int, char**) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("SDL Init");
    return 1;
  }
  SDL_GL_SetSwapInterval(1);

window = SDL_CreateWindow("Hello World",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            width,
                            height,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                           );
HandleResize();
#ifdef __EMSCRIPTEN__
  // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
  emscripten_set_main_loop(main_loop, 0, 1);
#else
  while (main_loop_running) {
    main_loop();
    SDL_Delay(16);
  }
#endif

  SDL_Quit();
}
