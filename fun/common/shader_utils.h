#ifndef _SHADER_UTILS_H
#define _SHADER_UTILS_H
#include <GL/glew.h>
void shader_gl_log_error(GLuint object);
GLuint shader_create_shader(const char* filename, GLenum type);
GLuint shader_create_program(const char* vertexfile, const char *fragmentfile);
#endif // _SHADER_UTILS_H
