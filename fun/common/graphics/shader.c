#include "graphics/shader.h"

#include "log.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------
static char* internal_file_read_malloc(const char* filename) {
  FILE* f = fopen(filename, "rb");
  if (!f) {
    LOG_ERROR("%s : %s : %s", "fopen", strerror(errno), filename);
    return 0x0;
  }

  size_t err = fseek(f, 0, SEEK_END);
  if (err) {
    LOG_ERROR("%s : %s : %s", "fseek", strerror(errno), filename);
    return 0x0;
  }
  unsigned int fsize = ftell(f);

  err = fseek(f, 0, SEEK_SET);  // rewind file
  if (err) {
    LOG_ERROR("%s : %s : %s", "fseek", strerror(errno), filename);
    return 0x0;
  }

  char* file_value = malloc(fsize + 1);
  fread(file_value, fsize, 1, f);
  file_value[fsize] = 0;

  err = fclose(f);
  if (err) {
    LOG_ERROR("%s : %s : %s", "fclose", strerror(errno), filename);
  }

  return file_value;
}

//--------------------------------------------------------------------------------
// This function was not tested much...
void graphics_shader_gl_log_error(GLuint object) {
  GLint log_length = 0;
  if (glIsShader(object)) {
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  } else if (glIsProgram(object)) {
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  } else {
    LOG_ERROR("Cannot find gl object information");
    return;
  }

  char* log = (char*)malloc(log_length);
  if (glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if (glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  LOG_ERROR("%s : %s", "graphics_shader_gl_log_error", log);
  free(log);
}

//--------------------------------------------------------------------------------
GLuint graphics_shader_create_shader(const char* filename, GLenum type) {
  const GLchar* source = internal_file_read_malloc(filename);
  if (!source) {
    LOG_ERROR("internal_file_read_malloc");
    return 0;
  }

  GLuint shader_obj = glCreateShader(type);
  // GLSL version
  const char* version;
  int profile;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
  if (profile == SDL_GL_CONTEXT_PROFILE_ES)
    version = "#version 100\n";  // OpenGL ES 2.0
  else
    version = "#version 120\n";  // OpenGL 2.1
  // GLES2 precision specifiers
  const char* precision =
      "#ifdef GL_ES                        \n"
      "#  ifdef GL_FRAGMENT_PRECISION_HIGH \n"
      "     precision highp float;         \n"
      "#  else                             \n"
      "     precision mediump float;       \n"
      "#  endif                            \n"
      "#else                               \n"
      // Ignore unsupported precision specifiers
      "#  define lowp                      \n"
      "#  define mediump                   \n"
      "#  define highp                     \n"
      "#endif                              \n";
  const GLchar* sources[] = {version, precision, source};
  glShaderSource(shader_obj, 3, sources, NULL);
  free((void*)source);

  glCompileShader(shader_obj);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    graphics_shader_gl_log_error(shader_obj);
    LOG_ERROR("glGetShaderiv : %s", filename);

    glDeleteShader(shader_obj);
    return 0;
  }

  return shader_obj;
}

//--------------------------------------------------------------------------------
GLuint graphics_shader_create_program(const char* vertexfile, const char* fragmentfile) {
  GLuint program = glCreateProgram();
  GLuint shader;
  if (vertexfile) {
    shader = graphics_shader_create_shader(vertexfile, GL_VERTEX_SHADER);
    if (!shader) return 0;
    glAttachShader(program, shader);
  }
  if (fragmentfile) {
    shader = graphics_shader_create_shader(fragmentfile, GL_FRAGMENT_SHADER);
    if (!shader) return 0;
    glAttachShader(program, shader);
  }
  glLinkProgram(program);
  GLint link_ok = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    LOG_ERROR("glLinkProgram");
    graphics_shader_gl_log_error(program);
    glDeleteProgram(program);
    return 0;
  }
  return program;
}
