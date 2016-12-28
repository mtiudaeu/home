#include "test/test.h"

#include "graphics/context.h"
#include "graphics/text.h"

//--------------------------------------------------------------------------------
//MDTMP
/*
void animate() {
  // alpha 0->1->0 every 5 seconds
  float cur_fade = sinf(SDL_GetTicks() / 1000.0 * (2 * 3.14) / 5) / 2 + 0.5;
  glUseProgram(program);
  glUniform1f(uniform_fade, cur_fade);
}
*/

//--------------------------------------------------------------------------------
void render() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
//MDTMP
/*

  glUseProgram(program);

  glEnableVertexAttribArray(attribute_coord2d);
  glEnableVertexAttribArray(attribute_v_color);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glVertexAttribPointer(
      attribute_coord2d,          // attribute
      2,                          // number of elements per vertex, here (x,y)
      GL_FLOAT,                   // the type of each element
      GL_FALSE,                   // take our values as-is
      sizeof(struct attributes),  // next coord2d appears every 5 floats
      0                           // offset of first element
      );
  glVertexAttribPointer(
      attribute_v_color,          // attribute
      3,                          // number of elements per vertex, here (r,g,b)
      GL_FLOAT,                   // the type of each element
      GL_FALSE,                   // take our values as-is
      sizeof(struct attributes),  // stride
      //(GLvoid*) (2 * sizeof(GLfloat))     // offset of first element
      (GLvoid*)offsetof(struct attributes, v_color)  // offset
      );

  // Push each element in buffer_vertices to the vertex shader 
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(attribute_coord2d);
  glDisableVertexAttribArray(attribute_v_color);
*/
}

//--------------------------------------------------------------------------------
void mainCallback() {
//MDTMP
/*
  animate();
*/
  render();
}

//--------------------------------------------------------------------------------
static size_t internal_test_integration()
{
  GraphicsText* graphics_text = graphics_text_from_tileset_malloc(
      "test/assets/Cooz_curses_square_16x16.png");

  //MDTMP
  const size_t ret = graphics_context_global_run(&mainCallback);


  TEST_ASSERT_TRUE_PTR(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

  return ret;
}

//--------------------------------------------------------------------------------
int main() {
  size_t ret;
/*
  size_t ret = graphics_context_test_run();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_context_test_run");
    return ret;
  }
*/

  graphics_context_global_init();

  ret = graphics_text_test_run();
  if (ret != 0) {
    TEST_ASSERT_MSG("graphics_text_test_run");
    return ret;
  }

  ret = internal_test_integration();
  if (ret != 0) {
    TEST_ASSERT_MSG("internal_test_integration");
    return ret;
  }

  graphics_context_global_uninit();

  return ret;
}
