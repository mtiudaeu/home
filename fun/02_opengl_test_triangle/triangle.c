#include "shader_utils.h"

#include "log.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <math.h>
#include <stdio.h>

SDL_Window* window;

GLuint vbo_triangle;
GLuint program;
GLint attribute_coord2d, attribute_v_color;
GLint uniform_fade;

struct attributes {
  GLfloat coord2d[2];
  GLfloat v_color[3];
};

int gl_resources_alloc() {
  struct attributes triangle_attributes[] = {{{0.0, 0.8}, {1.0, 1.0, 0.0}},
                                             {{-0.8, -0.8}, {0.0, 0.0, 1.0}},
                                             {{0.8, -0.8}, {1.0, 0.0, 0.0}}};
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes),
               triangle_attributes, GL_STATIC_DRAW);

  program = shader_create_program("triangle.v.glsl",  // vertex filename
                                  "triangle.f.glsl"   // fragment filename
                                  );
  if (!program) {
    LOG_ERROR("shader_create_program");
    return 1;
  }

  const char* attribute_name;
  attribute_name = "coord2d";
  attribute_coord2d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord2d == -1) {
    LOG_ERROR("glGetAttribLocation %s", attribute_name);
    return 1;
  }
  attribute_name = "v_color";
  attribute_v_color = glGetAttribLocation(program, attribute_name);
  if (attribute_v_color == -1) {
    LOG_ERROR("glGetAttribLocation %s", attribute_name);
    return 1;
  }
  const char* uniform_name;
  uniform_name = "fade";
  uniform_fade = glGetUniformLocation(program, uniform_name);
  if (uniform_fade == -1) {
    LOG_ERROR("glGetUniformLocation %s", uniform_name);
    return 1;
  }

  return 0;
}

void animate() {
  // alpha 0->1->0 every 5 seconds
  float cur_fade = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5) / 2 + 0.5;
  glUseProgram(program);
  glUniform1f(uniform_fade, cur_fade);
}

void render() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);

  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_v_color);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glVertexAttribPointer(
      attribute_coord2d,          // attribute
      2,                          // number of elements per vertex, here (x,y)
      GL_FLOAT,                   // the type of each element
      GL_FALSE,                   // take our values as-is
      sizeof(struct attributes),  // next coord2d appears every 5 floats
      0                           // offset of first element
      );
  glVertexAttribPointer(
      attribute_v_color,          // attribute
      3,                          // number of elements per vertex, here (r,g,b)
      GL_FLOAT,                   // the type of each element
      GL_FALSE,                   // take our values as-is
      sizeof(struct attributes),  // stride
      //(GLvoid*) (2 * sizeof(GLfloat))     // offset of first element
      (GLvoid*)offsetof(struct attributes, v_color)  // offset
      );

  /* Push each element in buffer_vertices to the vertex shader */
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(attribute_coord2d);
  glDisableVertexAttribArray(attribute_v_color);
  SDL_GL_SwapWindow(window);
}

void gl_resources_free() {
  glDeleteProgram(program);
  glDeleteBuffers(1, &vbo_triangle);
}

void mainCallback() {
  animate();
  render();
}

void mainLoop() {
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(&mainCallback,
                           0,  // fps
                           1   // simulate infinite loop
                           );
#else
  while (1) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_QUIT) return;
    }
    mainCallback();
  }
#endif
}

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("My Triangular Fade", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 640, 480,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  if (!window) {
    LOG_ERROR("SDL_CreateWindow %s", SDL_GetError());
    return 1;
  }

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
  return 0;
}
