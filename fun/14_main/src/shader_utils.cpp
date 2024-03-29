#include <fstream>
#include <sstream>

#include "common.h"
#include "shader_utils.h"
#include "gl_wrapper.h"

//--------------------------------------------------
static unsigned int compile_shader(unsigned int type,
                                   const std::string& path) {

  std::string source;
  {
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    source = buffer.str();
  }

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
    LOG_ERROR("Failed to compile shader : %s", path.c_str());
    LOG_ERROR("%s", message);
    glDeleteShader(id);
    return 0;
  }
  return id;
}

//--------------------------------------------------
unsigned int shader_utils::create_program(const std::string& vertex_path,
                            const std::string& fragment_path) {
  unsigned int program = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_path);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_path);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

//----------------------------------------------
void shader_utils::delete_program(unsigned int program) {
  glDeleteProgram(program);
}


