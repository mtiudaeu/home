#include "graphics/shader.h"

#include "common/log.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------
// FIXME This function was not tested much...
static void graphics_shader_gl_log_error(GLuint object) {
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
static char* graphics_shader_file_read_malloc(const char* filename) {
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
static GLuint graphics_shader_shader_create_str(const char* source,
                                                GLenum type) {
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

  glCompileShader(shader_obj);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(shader_obj, GL_COMPILE_STATUS, &compile_ok);
  if (compile_ok == GL_FALSE) {
    graphics_shader_gl_log_error(shader_obj);
    LOG_ERROR("glGetShaderiv");

    glDeleteShader(shader_obj);
    return 0;
  }

  return shader_obj;
}

//--------------------------------------------------------------------------------
static GLuint graphics_shader_shader_create_file(const char* filename,
                                                 GLenum type) {
  const GLchar* source = graphics_shader_file_read_malloc(filename);
  if (!source) {
    LOG_ERROR("graphics_shader_file_read_malloc");
    return 0;
  }

  const GLuint ret = graphics_shader_shader_create_str(source, type);
  free((void*)source);
  return ret;
}

//--------------------------------------------------------------------------------
static GLuint graphics_shader_program_create(GLuint vertex_shader,
                                             GLuint fragment_shader) {
  if (!vertex_shader) {
    LOG_ERROR("!vertex_shader");
    return 0;
  }
  if (!fragment_shader) {
    LOG_ERROR("!fragment_shader");
    return 0;
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);

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

//--------------------------------------------------------------------------------
GLuint graphics_shader_program_create_str(const char* vertex_source,
                                          const char* fragment_source) {
  const GLuint vertex_shader =
      graphics_shader_shader_create_str(vertex_source, GL_VERTEX_SHADER);
  if (!vertex_shader) {
    LOG_ERROR("!vertex_shader");
    return 0;
  }
  const GLuint fragment_shader =
      graphics_shader_shader_create_str(fragment_source, GL_FRAGMENT_SHADER);
  if (!fragment_shader) {
    LOG_ERROR("!fragment_shader");
    return 0;
  }

  return graphics_shader_program_create(vertex_shader, fragment_shader);
}

//--------------------------------------------------------------------------------
GLuint graphics_shader_program_create_file(const char* vertexfile,
                                           const char* fragmentfile) {
  const GLuint vertex_shader =
      graphics_shader_shader_create_file(vertexfile, GL_VERTEX_SHADER);
  if (!vertex_shader) {
    LOG_ERROR("!vertex_shader");
    return 0;
  }
  const GLuint fragment_shader =
      graphics_shader_shader_create_file(fragmentfile, GL_FRAGMENT_SHADER);
  if (!fragment_shader) {
    LOG_ERROR("!fragment_shader");
    return 0;
  }

  return graphics_shader_program_create(vertex_shader, fragment_shader);
}

//--------------------------------------------------------------------------------
GLuint graphics_shader_texture_buffer_create(const char* image_file_path) {
  GLuint tbo_texture = 0;

  SDL_Surface* tileset_texture = IMG_Load(image_file_path);
  if (!tileset_texture) {
    LOG_ERROR("IMG_Load: %s : %s", SDL_GetError(), image_file_path);
    return tbo_texture;
  }
  if (!tileset_texture->format) {
    LOG_ERROR("tileset_texture->format");
    return tbo_texture;
  }
  if (tileset_texture->format->BytesPerPixel != 4) {
    // This assumes GL_RGBA when calling glTexImage2D
    LOG_ERROR("tileset_texture->format->BytesPerPixel != 4");
    return tbo_texture;
  }

  glGenTextures(1, &tbo_texture);
  glBindTexture(GL_TEXTURE_2D, tbo_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,       // target
               0,                   // level, 0 = base, no minimap,
               GL_RGBA,             // internalformat
               tileset_texture->w,  // width
               tileset_texture->h,  // height
               0,                   // border, always 0 in OpenGL ES
               GL_RGBA,             // format
               GL_UNSIGNED_BYTE,    // type
               tileset_texture->pixels);
  SDL_FreeSurface(tileset_texture);

  return tbo_texture;
}
