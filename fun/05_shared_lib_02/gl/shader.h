#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H

#include <GL/glew.h>
GLuint shader_program_create_str(const char* vertex_source,
                                          const char* fragment_source);
GLuint shader_program_create_file(const char* vertex_file_path,
                                           const char* fragment_file_path);

GLuint shader_texture_buffer_create(const char* image_file_path);

#endif  // _SHADER_UTILS_H
