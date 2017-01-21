#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H

#include <GL/glew.h>
GLuint graphics_shader_program_create_str(const char* vertex_source,
                                          const char* fragment_source);
GLuint graphics_shader_program_create_file(const char* vertexfile,
                                           const char* fragmentfile);
#endif  // _SHADER_UTILS_H
