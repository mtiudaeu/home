#include "text.h"
#include "common.h"

namespace text {

struct Context {
  unsigned int texture;
  unsigned int program;
  unsigned int vbo;
};

//-----------------------------------------
Context* create() {
  unsigned char *data = stbi_load("assets/font.png", &width, &height, &nbChannels, 0);
  if(!data) {
    LOG_ERROR("!data");
    return nullptr;
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

  Context* context = new Context();
  context->texture = texture;

  return context;
}

//-----------------------------------------
void render(Context& context) {
}

//-----------------------------------------
Context* destroy(Context* context) {
 glDeleteTextures(1, &context->texture);
 delete context;
 return nullptr;
}

}

