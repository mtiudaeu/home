#include "gl_wrapper.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

//--------------------------------------------------
unsigned int create_texture(const char* path, int& width, int& height, int& nbChannels) {
  unsigned char *data = stbi_load(path, &width, &height, &nbChannels, 0);
  if(!data) {
    LOG_ERROR("!data");
    return 0;
  }

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
  GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  
  return texture;
}

//--------------------------------------------------
void destroy_texture(unsigned int texture) {
 glDeleteTextures(1, &texture);
}

