#include <SDL.h>

#include "glwrappers.h"
#include "shader_utils.h"
#include "tetris.h"

//--------------------------------------------------
struct TetrisImpl {
  unsigned int buffer;
  unsigned int program;
};

//--------------------------------------------------
Tetris::Tetris() : self(new TetrisImpl()) {
  glGenBuffers(1, &self->buffer);

  self->program =
      create_program("tetris.shader_v.txt", "tetris.shader_f.txt");
}

//--------------------------------------------------
Tetris::~Tetris() {}

//--------------------------------------------------
void Tetris::Render(SDL_Window* window, bool reset, float time_delta) {
  float positions[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};
  glBindBuffer(GL_ARRAY_BUFFER, self->buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
  glUseProgram(self->program);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

//--------------------------------------------------
void Tetris::ProcessEvent(SDL_Event* event) {}
