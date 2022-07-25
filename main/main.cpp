#include <SDL.h>
#include <SDL_opengl.h>

#include "global.h"
#include "common.h"

#include "ui.h"
#include "text.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

struct SideContext {
  UiContext* ui_context;
  text::Context* text_context;
};

struct MainContext {
  GlobalContext global_context;
  SideContext side_context;
  SDL_GLContext context_id;
  bool running;
};

static void handle_resize(MainContext& main_context) {
  GlobalContext& global_context = main_context.global_context;
  SDL_GL_GetDrawableSize(global_context.window, &global_context.width,
                         &global_context.height);
  glViewport(0, 0, global_context.width, global_context.height);
}

static void main_process_event(MainContext& main_context) {
  GlobalContext& global_context = main_context.global_context;

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        main_context.running = false;
        break;
      }
      case SDL_KEYUP: {
        int sym = event.key.keysym.sym;
        if (sym == SDLK_ESCAPE) {
          main_context.running = false;
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        LOG("Mouse have been cliked mdtmp!");
        SDL_MouseButtonEvent& mouse_event = event.button;
        LOG("x:%d,y:%d", mouse_event.x, mouse_event.y);
        break;
      }
      case SDL_WINDOWEVENT: {
        switch (event.window.event) {
          case SDL_WINDOWEVENT_SHOWN: {
            global_context.visible = true;
            break;
          }
          case SDL_WINDOWEVENT_HIDDEN: {
            global_context.visible = false;
            break;
          }
          case SDL_WINDOWEVENT_SIZE_CHANGED: {
            handle_resize(main_context);
            break;
          }
        }
        break;
      }
    }
  }
}

static void main_render(MainContext& main_context) {
  GlobalContext& global_context = main_context.global_context;

  unsigned int time_last = global_context.time_current;
  global_context.time_current = SDL_GetTicks();
  global_context.time_delta = (float)(global_context.time_current - time_last) / 1000.0f;

  SideContext& side_context = main_context.side_context;

  glClear(GL_COLOR_BUFFER_BIT);


  ui_render(global_context, *side_context.ui_context);
  text::render(*side_context.text_context);


  SDL_GL_SwapWindow(global_context.window);
}

static void main_loop(void* context_ptr) {
  MainContext& main_context = *((MainContext*)context_ptr);

  main_process_event(main_context);
  main_render(main_context);
}

static int main_init(MainContext& main_context) {
  {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      LOG_ERROR("SDL Init");
      LOG_ERROR("%s", SDL_GetError());
      return 1;
    }

/*
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);
*/

    GlobalContext& global_context = main_context.global_context;
    global_context.window = SDL_CreateWindow(
        "Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        global_context.width, global_context.height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (global_context.window == nullptr) {
      LOG_ERROR("SDL_CreateWindow");
      return 1;
    }
    main_context.context_id = SDL_GL_CreateContext(global_context.window);
    if (main_context.context_id == nullptr) {
      LOG_ERROR("SDL_GL_CreateContext");
      return 1;
    }
    SDL_UpdateWindowSurface(global_context.window);

    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    SDL_GL_GetDrawableSize(global_context.window, &global_context.width,
                         &global_context.height);
    glViewport(0, 0, global_context.width, global_context.height);

  }
 printf ("glGetString (GL_VERSION) returns %s\n", glGetString (GL_VERSION));

  SideContext& side_context = main_context.side_context; 

  side_context.ui_context = ui_create();
  side_context.text_context = text::create();

  handle_resize(main_context);

  return 0;
}

static void main_uninit(MainContext& main_context) {
  SideContext& side_context = main_context.side_context;

  side_context.ui_context = ui_destroy(side_context.ui_context);
  side_context.text_context = text::destroy(side_context.text_context);

  {
    SDL_GL_DeleteContext(main_context.context_id);
    SDL_DestroyWindow(main_context.global_context.window);
    SDL_Quit();
  }
}

int main(int, char**) {
  MainContext main_context = {.global_context =
                                  {
                                      .window = nullptr,
                                      .width = 800,
                                      .height = 600,
                                      .visible = true,

                                  },
                              .context_id = nullptr,
                              .running = true};

  if (main_init(main_context) != 0) {
    LOG_ERROR("init()");
    return 1;
  }

#ifdef __EMSCRIPTEN__
  // 0 fps means to use requestAnimationFrame; non-0 means to use setTimeout.
  // emscripten_set_main_loop(main_loop, 0, 1);
  emscripten_set_main_loop_arg(main_loop, &main_context, 0, 1);
#else
  while (main_context.running) {
    main_loop(&main_context);
    SDL_Delay(16);
  }
#endif
  main_uninit(main_context);
}
