#include "core/module_create.h"

#include <stdlib.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

struct context_s {
  SDL_Window* window = 0x0;
  SDL_GLContext gl_context = 0x0;
};
static context_s* context = 0x0;

static status_s context_uninit_cb() {
  assert(context);

  if (context->gl_context) {
    SDL_GL_DeleteContext(context->gl_context);
  }

  if (context->window) {
    SDL_DestroyWindow(context->window);
  }

  SDL_Quit();

  delete context;
  context = 0x0;

  return status_s();
}

static status_s context_init_cb(data_manager_s* /*data_manager*/) {
  context = new struct context_s();

  status_s status;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG_ERROR("SDL_Init : %s", SDL_GetError());
    status.error = true;
    return status;
  }

  context->window = SDL_CreateWindow(
      "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024,
      768, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!context->window) {
    LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
    context_uninit_cb();
    status.error = true;
    return status;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  context->gl_context = SDL_GL_CreateContext(context->window);
  if (context->gl_context == NULL) {
    LOG_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
    context_uninit_cb();
    status.error = true;
    return status;
  }

  // TODO validate if glewInit this need clean-up.
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    LOG_ERROR("glewInit %s", glewGetErrorString(glew_status));
    context_uninit_cb();
    status.error = true;
    return status;
  }
  if (!GLEW_VERSION_2_0) {
    LOG_ERROR("graphic card does not support OpenGL 2.0");
    context_uninit_cb();
    status.error = true;
    return status;
  }

  return status;
}


static status_s context_step_cb() {
  assert(context);

  SDL_GL_SwapWindow(context->window);

  return status_s();
}

MODULE_EXPORT(context_init_cb, context_uninit_cb, context_step_cb);

