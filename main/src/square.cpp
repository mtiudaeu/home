#include "square.h"

#include "shader_utils.h"
#include "assets.h"

#include "gl_wrapper.h"

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

namespace square {

static unsigned int program;
static unsigned int transform;
static unsigned int vbo;
static unsigned int ebo;

//--------------------------------------------------
void init() {
  program = shader_utils::create_program(SHADER_SQUARE_V_PATH, SHADER_SQUARE_F_PATH);
  glUseProgram(program);
  transform = glGetUniformLocation(program, "transform");  
  
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  
  float vertices [] = {
      0.5f, 0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f, -0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f
  };
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
  };
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

//--------------------------------------------------
void uninit() {
 shader_utils::delete_program(program);
 
 glDeleteBuffers(1, &vbo);
 glDeleteBuffers(1, &ebo);
}

//--------------------------------------------------
void render(Ctx& ctx) {
  glUseProgram(program);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

//mdtmp
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::scale(trans, glm::vec3(0.1f, 0.1f, 0.1f));
  trans = glm::scale(trans, glm::vec3(ctx.width, ctx.height, 1.0f));
  trans = glm::translate(trans, glm::vec3(ctx.x, ctx.y, 0.0f));
  glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(trans));


  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);

}

}

