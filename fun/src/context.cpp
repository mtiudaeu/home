#include "module.h"

#include "log.h"

#include <assert.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

struct context {
  SDL_Window* window = 0x0;
  SDL_GLContext gl_context = 0x0;
  void (*main_loop_cb)(float) = 0x0;           // MDTMP stil needed?
  void (*handle_hotkey_cb)(SDL_Event*) = 0x0;  // MDTMP stil needed?
  size_t leave_main_loop = 0;                  // MDTMP change to bool?
  int time_current = 0;
  int time_last = 0;
};
// MDTMP
/*
static struct graphics_context* global_graphics_context;

static void graphics_context_main_loop() {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      global_graphics_context->leave_main_loop = 1;
      return;
    }
    if (global_graphics_context->handle_hotkey_cb) {
      global_graphics_context->handle_hotkey_cb(&ev);
    }
  }

  global_graphics_context->time_current = SDL_GetTicks();
  const float time_delta = (float)(global_graphics_context->time_current -
                                   global_graphics_context->time_last) /
                           1000.0f;
  global_graphics_context->time_last = global_graphics_context->time_current;

  global_graphics_context->main_loop_cb(time_delta);
  SDL_GL_SwapWindow(global_graphics_context->window);
}

size_t graphics_context_global_init()
{
  if (global_graphics_context) {
    LOG_ERROR("global_graphics_context already initialize")
    return 1;
  }

  {  // OpenGL related
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      LOG_ERROR("SDL_Init : %s", SDL_GetError());
      return 1;
    }

    global_graphics_context = calloc(1, sizeof(*global_graphics_context));
    global_graphics_context->window = SDL_CreateWindow(
        "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1024, 768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!global_graphics_context->window) {
      graphics_context_global_uninit();
      LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
      return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    global_graphics_context->gl_context =
        SDL_GL_CreateContext(global_graphics_context->window);
    if (global_graphics_context->gl_context == NULL) {
      graphics_context_global_uninit();
      LOG_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
      return 1;
    }

    // TODO validate if glewInit this need clean-up.
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
      LOG_ERROR("glewInit %s", glewGetErrorString(glew_status));
      graphics_context_global_uninit();
      return 1;
    }
    if (!GLEW_VERSION_2_0) {
      LOG_ERROR("graphic card does not support OpenGL 2.0");
      graphics_context_global_uninit();
      return 1;
    }
  }

  return 0;
}

size_t graphics_context_global_uninit()
{
  {  // OpenGL related
    if (!global_graphics_context) {
      LOG_ERROR("global_graphics_context is not initialize")
      return 1;
    }

    if (global_graphics_context->gl_context) {
      SDL_GL_DeleteContext(global_graphics_context->gl_context);
    }

    if (global_graphics_context->window) {
      SDL_GL_DeleteContext(global_graphics_context->window);
    }

    SDL_Quit();
  }

  free(global_graphics_context);
  global_graphics_context = 0x0;

  return 0;
}

size_t graphics_context_global_run(void (*main_loop_cb)(float),
                                   void (*handle_hotkey_cb)(SDL_Event*)) {
  if (!global_graphics_context) {
    LOG_ERROR("global_graphics_context is not initialize");
    return 1;
  }
  if (!main_loop_cb) {
    LOG_ERROR("main_loop_cb is null");
    return 1;
  }

  { // prepare loop callbacks.
    global_graphics_context->main_loop_cb = main_loop_cb;
    if (handle_hotkey_cb) {
      global_graphics_context->handle_hotkey_cb = handle_hotkey_cb;
    }

    global_graphics_context->time_current = SDL_GetTicks();
    global_graphics_context->time_last = global_graphics_context->time_current;
  }


  while (global_graphics_context->leave_main_loop == 0) {
    graphics_context_main_loop();
  }

  return 0;
}
*/

static void context_uninit_state(void* state);

static void* context_init_state() {
  context* context = 0x0;
  {  // OpenGL related
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      LOG_ERROR("SDL_Init : %s", SDL_GetError());
      return 0x0;
    }

    context = new struct context();
    context->window = SDL_CreateWindow(
        "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1024, 768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!context->window) {
      LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
      context_uninit_state(context);
      context = 0x0;
      return 0x0;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    context->gl_context = SDL_GL_CreateContext(context->window);
    if (context->gl_context == NULL) {
      LOG_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
      context_uninit_state(context);
      context = 0x0;
      return 0x0;
    }

    // TODO validate if glewInit this need clean-up.
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
      LOG_ERROR("glewInit %s", glewGetErrorString(glew_status));
      context_uninit_state(context);
      context = 0x0;
      return 0x0;
    }
    if (!GLEW_VERSION_2_0) {
      LOG_ERROR("graphic card does not support OpenGL 2.0");
      context_uninit_state(context);
      context = 0x0;
      return 0x0;
    }
  }

  return context;
}

static void context_uninit_state(void* state) {
  if (!state) {
    LOG_ERROR("!state");
    return;
  }

  struct context* context = static_cast<struct context*>(state);
  {  // OpenGL related

    if (context->gl_context) {
      SDL_GL_DeleteContext(context->gl_context);
    }

    if (context->window) {
      SDL_GL_DeleteContext(context->window);
    }

    SDL_Quit();
  }

  delete context;
  context = 0x0;
}

static void context_load_state(void*  // state
                               ) {
  printf("context_: context_load_state\n");
}

static void context_unload_state(void*  // state
                                 ) {
  printf("context_: context_unload_state\n");
}

static bool context_step(void* state) {
  printf("context_: omg\n");
  if (!state) {
    LOG_ERROR("!state");
    return false;
  }
  struct context* context = static_cast<struct context*>(state);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  SDL_GL_SwapWindow(context->window);

  return true;
}

MODULE_EXPORT_API(context_init_state, context_uninit_state, context_load_state,
                  context_unload_state, context_step);
