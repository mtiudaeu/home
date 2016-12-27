#include "graphics/context.h"

#include "log.h"

#include <stdlib.h>
#include <assert.h>

/*
SDL_Init(SDL_INIT_VIDEO);
window = SDL_CreateWindow(
SDL_GLContext glcontext = SDL_GL_CreateContext(window);


SDL_GL_DeleteContext(glcontext); 
SDL_DestroyWindow(window);
SDL_Quit();

*/

typedef struct {
//MDTMP review name etc..
  SDL_Window* window;
  SDL_GLContext gl_context;
  GLuint program_id; //MDTMP needed?
} InternalGraphicsContext;

//--------------------------------------------------------------------------------
static InternalGraphicsContext* internal_graphics_context_malloc() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        fprintf(stderr,
                "\nUnable to initialize SDL:  %s\n",
                SDL_GetError()
               );
        return 1;
    }
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Default Parameter", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 640, 480,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!window) {
    //FIXME SDL_Init is not cleaned up
    LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
    return 0x0;
  }
/*
SDL_GLContext glcontext = SDL_GL_CreateContext(window);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  if (SDL_GL_CreateContext(window) == NULL) {
    LOG_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
    return 1;
  }

  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    LOG_ERROR("glewInit %s", glewGetErrorString(glew_status));
    return 1;
  }
  if (!GLEW_VERSION_2_0) {
    LOG_ERROR("graphic card does not support OpenGL 2.0");
    return 1;
  }

  if (gl_resources_alloc() != 0) {
    return 1;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  mainLoop();

  gl_resources_free();
*/
//MDTMP remove
  InternalGraphicsContext* graphics_context = malloc(sizeof(InternalGraphicsContext));
  // MDTMP set program_id and initialize program context
  graphics_context->program_id = 0;
  return graphics_context;
}

//--------------------------------------------------------------------------------
//MDTMP remove
static void internal_graphics_context_free(InternalGraphicsContext* graphics_context) {
  assert(graphics_context);
  // MDTMP uninitialize program_id
  free(graphics_context);
}

static InternalGraphicsContext* global_graphics_context;
//--------------------------------------------------------------------------------
void graphics_context_global_init()
{
  if (global_graphics_context) {
    LOG_ERROR("global_graphics_context already initialize")
    return;
  }
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    LOG_ERROR("SDL_Init : %s", SDL_GetError());
    return;
  }

  global_graphics_context = calloc(1, sizeof(*global_graphics_context));
  global_graphics_context->window = SDL_CreateWindow(
      "Default Parameter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,
      480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!global_graphics_context->window) {
    graphics_context_global_uninit();
    LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  global_graphics_context->gl_context =
      SDL_GL_CreateContext(global_graphics_context->window);
  if (global_graphics_context->gl_context == NULL) {
    graphics_context_global_uninit();
    LOG_ERROR("SDL_GL_CreateContext %s", SDL_GetError());
    return;
  }

  // TODO validate if glewInit this need clean-up.
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK) {
    LOG_ERROR("glewInit %s", glewGetErrorString(glew_status));
    graphics_context_global_uninit();
    return;
  }
  if (!GLEW_VERSION_2_0) {
    LOG_ERROR("graphic card does not support OpenGL 2.0");
    graphics_context_global_uninit();
    return;
  }
}

//--------------------------------------------------------------------------------
void graphics_context_global_uninit()
{
  if (!global_graphics_context) {
    LOG_ERROR("global_graphics_context is not initialize")
    return;
  }

  if (global_graphics_context->gl_context != NULL) {
    // MDTMP test if is null by default with calloc default.
    SDL_GL_DeleteContext(global_graphics_context->gl_context);
  }

  if (global_graphics_context->window) {
    // MDTMP test if is null by default with calloc default.
    SDL_GL_DeleteContext(global_graphics_context->window);
  }

  SDL_Quit();

  free(global_graphics_context);
  global_graphics_context = 0x0;
}

//--------------------------------------------------------------------------------
void graphics_context_global_run()
{
//MDTMP do main loop
}


