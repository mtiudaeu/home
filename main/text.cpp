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
  std::string value;
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


  glGenBuffers(1, &context->vbo);

  return context;
}

//-----------------------------------------
void render(Context& context) {
  if(context.value.empty()) return;

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

//-----------------------------------------
void set_value(Context& context, const std::string& value) {
  context.value = value;

  float vertices[] = {
  0.5f, 0.5f, 0.0f,1.0f, 1.0f, // top right
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // top left
  0.5f, 0.5f, 0.0f,1.0f, 1.0f, // top right
  };
  glBindBuffer(GL_ARRAY_BUFFER, context.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glUseProgram(context.program);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

}

}
/*
//--------------------------------------------------------------------------------
static struct grid_16x16 graphics_text_char_to_grid_coord(char value) {
  struct grid_16x16 coord;
  coord.x = value % 16; 
  coord.y = value / 16; 
  return coord;
}

//--------------------------------------------------------------------------------
#define TEXTURE_CHARACTER_WIDTH 1.0f / 16.0f
#define TEXTURE_CHARACTER_HEIGHT 1.0f / 16.0f

//--------------------------------------------------------------------------------
// rectangle_2D (0.0,0.0) is bottom left
static void graphics_text_rectangle_2D_texture(struct rectangle_2d* rectangle_2D, char value) {
  assert(rectangle_2D);

  const struct grid_16x16 character_coord = graphics_text_char_to_grid_coord(value);
  rectangle_2D->x = character_coord.x * TEXTURE_CHARACTER_WIDTH;
  rectangle_2D->y = 1.0f - (character_coord.y  * TEXTURE_CHARACTER_HEIGHT) - TEXTURE_CHARACTER_HEIGHT;
  rectangle_2D->width = TEXTURE_CHARACTER_WIDTH;
  rectangle_2D->height = TEXTURE_CHARACTER_HEIGHT;
}

*/

