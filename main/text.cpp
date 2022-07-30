#include "text.h"
#include "common.h"
#include "shader_utils.h"
#include "gl_wrapper.h"
#include "assets.h"
#include <stb/stb_image.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace text {

//--------------------------------------------------------------------------------
static const float TEXTURE_CHARACTER_WIDTH  = 1.0f / 16.0f;
static const float TEXTURE_CHARACTER_HEIGHT = 1.0f / 8.0f;

struct Context {
  unsigned int texture;
  unsigned int program;
  unsigned int vbo;
  unsigned int ebo;
  unsigned int transform;
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

  context->program = shader_utils::create_program(SHADER_FONT_V_PATH, SHADER_FONT_F_PATH);
  context->transform = glGetUniformLocation(context->program, "transform"); 

  glGenBuffers(1, &context->vbo);
  glGenBuffers(1, &context->ebo);

  return context;
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
void render(Context& context) {
  if(context.value.empty()) return;

  glUseProgram(context.program);

  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::scale(trans, glm::vec3(0.1f, 0.1f, 0.1f));

  for(int i = 0; i < 2; i ++) {
    trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));
    
    glUniformMatrix4fv(context.transform, 1, GL_FALSE, glm::value_ptr(trans));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.ebo);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }

}

//-----------------------------------------
void set_value(Context& context, const std::string& value) {
  context.value = value;

  char c = 'b';

  float x0 = (c % 16) * TEXTURE_CHARACTER_WIDTH - (TEXTURE_CHARACTER_WIDTH / 10.0f);  
  float y0 = 1.0f - ((c / 16) * TEXTURE_CHARACTER_HEIGHT) - TEXTURE_CHARACTER_HEIGHT; 
  //float y0 = (c / 16) * TEXTURE_CHARACTER_HEIGHT; 
  float x1 = x0 + (TEXTURE_CHARACTER_WIDTH * 0.6f);
  float y1 = y0 + TEXTURE_CHARACTER_HEIGHT;

  LOG("x0 %f", x0);
  LOG("y0 %f", y0);
  LOG("x1 %f", x1);
  LOG("y1 %f", y1);

  float vertices[] = {
  0.5f, 0.5f, 0.0f, x1, y1, // top right
  0.5f, -0.5f, 0.0f, x1, y0, // bottom right
  -0.5f, -0.5f, 0.0f, x0, y0, // bottom left
  -0.5f, 0.5f, 0.0f, x0, y1 // top left
  };

  glBindBuffer(GL_ARRAY_BUFFER, context.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int indices[] = {
    0,1,2,
    2,3,0
  };
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

