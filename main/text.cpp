#include "text.h"
#include "common.h"
#include "shader_utils.h"
#include "gl_wrapper.h"
#include <stb/stb_image.h>

namespace text {

struct Context {
  unsigned int texture;
  unsigned int program;
  unsigned int vbo;
};

//-----------------------------------------
Context* create() {
  int width, height, nbChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("assets/font.png", &width, &height, &nbChannels, 0);
  if(!data) {
    LOG_ERROR("!data");
    return nullptr;
  }
  Context* context = new Context();
  {

   glGenTextures(1, &context->texture);
   glBindTexture(GL_TEXTURE_2D, context->texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
     GL_UNSIGNED_BYTE, data);
   glGenerateMipmap(GL_TEXTURE_2D);

   stbi_image_free(data);
  }

  context->program = shader_utils::create_program("assets/font.shader_v.txt", "assets/font.shader_f.txt");

  float vertices[] = {
  0.5f, 0.5f, 0.0f,1.0f, 1.0f, // top right
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
  0.5f, 0.5f, 0.0f,1.0f, 1.0f, // top right
  };

  glGenBuffers(1, &context->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, context->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glUseProgram(context->program);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  return context;
}

//-----------------------------------------
void render(Context& context) {
  glUseProgram(context.program);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

//-----------------------------------------
Context* destroy(Context* context) {
 shader_utils::delete_program(context->program);
 context->program = 0;

 glDeleteTextures(1, &context->texture);
 delete context;

 return nullptr;
}

}

