#include "ui.h"

#include "common.h"
#include "gl_wrapper.h"
#include "shader_utils.h"

struct UiContext : nocopy {
  unsigned int program;
};

//----------------------------------------
static void init(UiContext& ui_context) {
  ui_context.program =
      shader_utils::create_program("ui.shader_v.txt", "ui.shader_f.txt");

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glUseProgram(ui_context.program);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

//----------------------------------------
UiContext* ui_create() {
  UiContext* ui_context = new UiContext();

  init(*ui_context);

  return ui_context;
}

//----------------------------------------
void ui_render(const GlobalContext& global_context, UiContext& ui_context) {
  glUseProgram(ui_context.program);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

//----------------------------------------
UiContext* ui_destroy(UiContext* ui_context) {
  shader_utils::delete_program(ui_context->program);
  ui_context->program = 0;

  return ui_context;
}
