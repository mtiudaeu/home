#include "common/graphics/context.h"

#include "common/test/test.h"

#include "common/log.h"

#include <stdlib.h>
#include <assert.h>

#include <GL/glew.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

typedef struct {
  SDL_Window* window;
  SDL_GLContext gl_context;
  void (*main_loop_cb)(SDL_Event*);
  size_t leave_main_loop;
} InternalGraphicsContext;
static InternalGraphicsContext* global_graphics_context;

//--------------------------------------------------------------------------------
size_t graphics_context_global_init()
{
  if (global_graphics_context) {
    LOG_ERROR("global_graphics_context already initialize")
    return 1;
  }

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG_ERROR("SDL_Init : %s", SDL_GetError());
    return 1;
  }

  global_graphics_context = calloc(1, sizeof(*global_graphics_context));
  global_graphics_context->window = SDL_CreateWindow(
      "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,
      480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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

  return 0;
}

//--------------------------------------------------------------------------------
size_t graphics_context_global_uninit()
{
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

  free(global_graphics_context);
  global_graphics_context = 0x0;

  return 0;
}

//--------------------------------------------------------------------------------
void internal_main_loop() {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    if (ev.type == SDL_QUIT) {
      global_graphics_context->leave_main_loop = 1;
      return;
    }
  }

  global_graphics_context->main_loop_cb(&ev);
  SDL_GL_SwapWindow(global_graphics_context->window);
}

//--------------------------------------------------------------------------------
size_t graphics_context_global_run(void (*main_loop_cb)(SDL_Event*)) {
  if (!global_graphics_context) {
    LOG_ERROR("global_graphics_context is not initialize");
    return 1;
  }
  if (!main_loop_cb) {
    LOG_ERROR("main_loop_cb is null");
    return 1;
  }
  global_graphics_context->main_loop_cb = main_loop_cb;

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(&internal_main_loop,
                           0,  // fps
                           1   // simulate infinite loop
                           );
#else
  while (global_graphics_context->leave_main_loop == 0) {
    internal_main_loop();
  }
#endif

  return 0;
}

//--------------------------------------------------------------------------------
size_t graphics_context_global_ready()
{
  return global_graphics_context == 0;
}

//--------------------------------------------------------------------------------
#ifdef INCLUDE_RUN_TEST
size_t graphics_context_run_test()
{
  size_t ret = graphics_context_global_init();
  TEST_ASSERT_MSG("graphics_context_global_init", ret);
  if (ret != 0) {
    return ret;
  }
  ret = graphics_context_global_uninit();
  TEST_ASSERT_MSG("graphics_context_global_uninit", ret);
  if (ret != 0) {
    return ret;
  }
  return ret;
}
#endif  // INCLUDE_RUN_TEST
