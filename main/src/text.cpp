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

static unsigned int texture;
static unsigned int program;
static unsigned int vbo;
static unsigned int ebo;
static unsigned int transform;


//-----------------------------------------
void init() {
  int width, height, nbChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("assets/font.png", &width, &height, &nbChannels, 0);
  if(!data) {
    LOG_ERROR("!data");
    return;
  }

  {

   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
     GL_UNSIGNED_BYTE, data);
   glGenerateMipmap(GL_TEXTURE_2D);

   stbi_image_free(data);
  }

  program = shader_utils::create_program(SHADER_FONT_V_PATH, SHADER_FONT_F_PATH);
  transform = glGetUniformLocation(program, "transform"); 

  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  {
    glUseProgram(program);

    //             rows * columns * corners * (vertices+textures)
    float vertices[  16 *       8 *       4 *                  5];

    for(int i = 0; i < (16*8); i++) {
      float x0 = (i % 16) * TEXTURE_CHARACTER_WIDTH - (TEXTURE_CHARACTER_WIDTH / 10.0f);  
      float y0 = 1.0f - ((i / 16) * TEXTURE_CHARACTER_HEIGHT) - TEXTURE_CHARACTER_HEIGHT; 
      float x1 = x0 + (TEXTURE_CHARACTER_WIDTH * 0.6f);
      float y1 = y0 + TEXTURE_CHARACTER_HEIGHT;

      int start_idx = i * 4 * 5;
      // top right
      vertices[start_idx + 0] = 0.5f;
      vertices[start_idx + 1] = 0.5f;
      vertices[start_idx + 2] = 0.0f;
      vertices[start_idx + 3] = x1;
      vertices[start_idx + 4] = y1;
      //bottom right
      vertices[start_idx + 5] = 0.5f;
      vertices[start_idx + 6] = -0.5f;
      vertices[start_idx + 7] = 0.0f;
      vertices[start_idx + 8] = x1;
      vertices[start_idx + 9] = y0;
      //bottom left
      vertices[start_idx + 10] = -0.5f;
      vertices[start_idx + 11] = -0.5f;
      vertices[start_idx + 12] = 0.0f;
      vertices[start_idx + 13] = x0;
      vertices[start_idx + 14] = y0;
      //top left
      vertices[start_idx + 15] = -0.5f;
      vertices[start_idx + 16] = 0.5f;
      vertices[start_idx + 17] = 0.0f;
      vertices[start_idx + 18] = x0;
      vertices[start_idx + 19] = y1;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

  }
}

//-----------------------------------------
void uninit() {
 shader_utils::delete_program(program);
 glDeleteTextures(1, &texture);
 glDeleteBuffers(1, &vbo);
 glDeleteBuffers(1, &ebo);
}

//-----------------------------------------
void render(Context& context) {
  if(context.value.empty()) return;

  glUseProgram(program);

  glm::mat4 trans = glm::mat4(1.0f);
  // default scale
  trans = glm::scale(trans, glm::vec3(0.1f, 0.1f, 0.1f));
  trans = glm::scale(trans, glm::vec3(context.size, context.size, context.size));
  trans = glm::translate(trans, glm::vec3(context.x, context.y, 0.0f));

  for(auto c: context.value) {
    unsigned int indices_start = c * 4;
    unsigned int indices[] = {
      indices_start + 0,
      indices_start + 1,
      indices_start + 2,
      indices_start + 2,
      indices_start + 3,
      indices_start + 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(trans));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));
  }

}

}
