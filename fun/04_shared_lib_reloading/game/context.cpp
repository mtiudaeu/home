#include "core/log.h"
#include "core/module.h"

#include <assert.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

struct context {
  SDL_Window* window = 0x0;
  SDL_GLContext gl_context = 0x0;
};

static module_status context_unload_state(void* state);

static void* context_init_state(module_status&, void**, size_t) {
  return new struct context();
}

static module_status context_uninit_state(void* state) {
  assert(state);
  context* context = static_cast<struct context*>(state);

  delete context;
  context = 0x0;

  return module_status();
}

static module_status context_load_state(void* state) {
  assert(state);

  module_status load_status;
  context* context = static_cast<struct context*>(state);
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG_ERROR("SDL_Init : %s", SDL_GetError());
    load_status.error = true;
    return load_status;
  }

  context->window = SDL_CreateWindow(
      "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024,
      768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!context->window) {
    LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
    context_unload_state(context);
    load_status.error = true;
    return load_status;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  context->gl_context = SDL_GL_CreateContext(context->window);
  if (context->gl_context == NULL) {
    LOG_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
    context_unload_state(context);
    load_status.error = true;
    return load_status;
  }

  // TODO validate if glewInit this need clean-up.
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    LOG_ERROR("glewInit %s", glewGetErrorString(glew_status));
    context_unload_state(context);
    load_status.error = true;
    return load_status;
  }
  if (!GLEW_VERSION_2_0) {
    LOG_ERROR("graphic card does not support OpenGL 2.0");
    context_unload_state(context);
    load_status.error = true;
    return load_status;
  }
  return load_status;
}

static module_status context_unload_state(void* state) {
  assert(state);
  context* context = static_cast<struct context*>(state);
  {  // OpenGL related

    if (context->gl_context) {
      SDL_GL_DeleteContext(context->gl_context);
    }

    if (context->window) {
      SDL_DestroyWindow(context->window);
    }

    SDL_Quit();
  }
  return module_status();
}

static module_status context_step(void* state) {
  assert(state);

  struct context* context = static_cast<struct context*>(state);
  SDL_GL_SwapWindow(context->window);

  return module_status();
}

MODULE_EXPORT_API(context_init_state, context_uninit_state, context_load_state,
                  context_unload_state, context_step);
