#include "square.h"

#include "shader_utils.h"
#include "assets.h"

#include "gl_wrapper.h"

namespace square {

struct Ctx {
  unsigned int program;
  unsigned int transform;
  unsigned int vbo;
  unsigned int ebo;
};

//--------------------------------------------------
Ctx* create() {
  Ctx* ctx = new Ctx();

  ctx->program = shader_utils::create_program(SHADER_SQUARE_V_PATH, SHADER_SQUARE_F_PATH);
  ctx->transform = glGetUniformLocation(ctx->program, "transform");  
  
  glGenBuffers(1, &ctx->vbo);
  glGenBuffers(1, &ctx->ebo);

  return ctx;
}

//--------------------------------------------------
Ctx* destroy(Ctx* ctx) {
  delete ctx;
  return nullptr;
}

//--------------------------------------------------
void render(Ctx& ctx) {
}

}

