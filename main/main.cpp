#include <SDL.h>
#include <SDL_opengl.h>

#include "common.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

struct MainContext {
  SDL_Window* window;
  SDL_GLContext context_id;
  int width;
  int height;
  bool visible;
  bool running;
};

static void HandleResize(MainContext& context) {
  SDL_GL_GetDrawableSize(context.window, &context.width, &context.height);
  glViewport(0, 0, context.width, context.height);
}

static void main_loop(void* context_ptr) {
  MainContext& context = *((MainContext*)context_ptr);

  {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT: {
          context.running = false;
          break;
        }
        case SDL_KEYUP: {
          int sym = event.key.keysym.sym;
          if (sym == SDLK_ESCAPE) {
            context.running = false;
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
          context.visible = true;
          break;
        }
        case SDL_WINDOWEVENT_HIDDEN: {
          context.visible = false;
          break;
        }
        case SDL_WINDOWEVENT_SIZE_CHANGED: {
          HandleResize(context);
          break;
        }
      }
    }
  }

  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(context.window);
}

static int main_init(MainContext& context) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    LOG_ERROR("SDL Init");
    LOG_ERROR("%s", SDL_GetError());
    return 1;
  }

  context.window = SDL_CreateWindow(
      "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      context.width, context.height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if (context.window == nullptr) {
    LOG_ERROR("SDL_CreateWindow");
    return 1;
  }
  context.context_id = SDL_GL_CreateContext(context.window);
  if (context.context_id == nullptr) {
    LOG_ERROR("SDL_GL_CreateContext");
    return 1;
  }
  SDL_UpdateWindowSurface(context.window);

  SDL_GL_SetSwapInterval(1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  HandleResize(context);

  return 0;
}

static void main_uninit(MainContext& context) {
  SDL_GL_DeleteContext(context.context_id);
  SDL_DestroyWindow(context.window);
  SDL_Quit();
}

int main(int, char**) {
  MainContext context = {.window = nullptr,
                         .context_id = nullptr,
                         .width = 800,
                         .height = 600,
                         .visible = true,
                         .running = true};

  if (main_init(context) != 0) {
    LOG_ERROR("init()");
    return 1;
  }

#ifdef __EMSCRIPTEN__
  // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
  // emscripten_set_main_loop(main_loop, 0, 1);
  emscripten_set_main_loop_arg(main_loop, &context, 0, 1);
#else
  while (context.running) {
    main_loop(&context);
    SDL_Delay(16);
  }
#endif
  main_uninit(context);
}
