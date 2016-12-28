#include "graphics/context.h"

#include "test/test.h"

#include "log.h"

#include <stdlib.h>
#include <assert.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

typedef struct {
  SDL_Window* window;
  SDL_GLContext gl_context;
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
size_t graphics_context_global_run(void (*render_cb)()) {
  if (!global_graphics_context) {
    LOG_ERROR("global_graphics_context is not initialize")
    return 1;
  }
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(&render_cb,
                           0,  // fps
                           1   // simulate infinite loop
                           );
//MDTMP register a main callback to the Context
//MDTMP create  main internal main function which call this register + Swap window
//MDTMP add to emscripten SDL_GL_SwapWindow(window);
#else
  while (1) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_QUIT) return 0;
    }
    render_cb();
    SDL_GL_SwapWindow(global_graphics_context->window);
  }
#endif

  return 0;
}


//--------------------------------------------------------------------------------
#ifdef INCLUDE_RUN_TEST
size_t graphics_context_test_run()
{
  size_t ret = graphics_context_global_init();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_context_global_init");
    return ret;
  }
  ret = graphics_context_global_uninit();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_context_global_uninit");
    return ret;
  }
  return ret;
}
#endif  // INCLUDE_RUN_TEST
