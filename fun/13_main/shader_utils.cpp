#include <fstream>
#include <sstream>

#include "common.h"
#include "glwrappers.h"

//--------------------------------------------------
static unsigned int compile_shader(unsigned int type,
                                   const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    LOG_ERROR("Failed to compile shader!");
    LOG_ERROR("%s", message);
    glDeleteShader(id);
    return 0;
  }
  return id;
}

//--------------------------------------------------
unsigned int create_program(const std::string& vertex_path,
                            const std::string& fragment_path) {
  std::string vertex_shader;
  std::string fragment_shader;

  {
    std::ifstream t(vertex_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    vertex_shader = buffer.str();
  }
  {
    std::ifstream t(fragment_path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    fragment_shader = buffer.str();
  }

  unsigned int program = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}
