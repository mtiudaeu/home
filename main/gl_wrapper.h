#ifndef GL_WRAPPERS_H
#define GL_WRAPPERS_H

#define GL_GLEXT_PROTOTYPES
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_opengl_glext.h>

#include "common.h"

unsigned int create_texture(const char* path, int& width, int& height, int& nbChannels);
void destroy_texture(unsigned int texture);

#endif
