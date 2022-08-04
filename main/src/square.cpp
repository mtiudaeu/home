#include "square.h"

#include "shader_utils.h"
#include "assets.h"

#include "gl_wrapper.h"

namespace square {

static unsigned int program;
static unsigned int transform;
static unsigned int vbo;
static unsigned int ebo;

//--------------------------------------------------
void init() {
  program = shader_utils::create_program(SHADER_SQUARE_V_PATH, SHADER_SQUARE_F_PATH);
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

  glUseProgram(program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

 

}

//--------------------------------------------------
void uninit() {
 shader_utils::delete_program(program);
 
 glDeleteBuffers(1, &vbo);
 glDeleteBuffers(1, &ebo);
}

//--------------------------------------------------
//void render(Ctx& ctx) {
void render() {
    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

}

