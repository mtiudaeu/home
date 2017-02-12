#include "common/graphics/text/text.h"

#include "common/graphics/point.h"
#include "common/graphics/context.h"

#include "common/graphics/primitive/rectangle_2D.h"
#include "common/graphics/shader.h"

#include "common/test/test.h"

#include "common/log/log.h"

#include <GL/glew.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "common/graphics/text/square_texture.h"
#include "common/graphics/text/square_vertices.h"

//--------------------------------------------------------------------------------
struct GraphicsText {
  GLuint tbo_texture_tileset;
};

//--------------------------------------------------------------------------------
GraphicsText* graphics_text_calloc() {
  if (graphics_context_global_ready() != 0) {
    LOG_ERROR("graphics_context_global_ready != 0");
    return 0x0;
  }
  GraphicsText* graphics_text = calloc(1, sizeof(GraphicsText));

  {  // Create texture map objects
    const char* tileset_filename = "common/assets/text/ASCII_tileset.png";
    graphics_text->tbo_texture_tileset =
        graphics_shader_texture_buffer_create(tileset_filename);
    if (!graphics_text->tbo_texture_tileset) {
      LOG_ERROR("!graphics_text->tbo_texture_tileset");
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  return graphics_text;
}

//--------------------------------------------------------------------------------
void graphics_text_free(GraphicsText* graphics_text) {
  assert(graphics_text);

  glDeleteTextures(1, &graphics_text->tbo_texture_tileset);

  free(graphics_text);
}

//--------------------------------------------------------------------------------
// FIXME  Could accumulate all text to draw on screen and call glDrawArray once.
void graphics_text_draw(const GraphicsText* graphics_text, float scale,
                        GraphicsPoint2D position, const char* msg) {
  assert(graphics_text);
  if (!msg || !msg[0]) {
    LOG_ERROR("graphics_text_draw : invalid msg");
  }


  const size_t length_msg = strlen(msg);

  const size_t rectangle_2D_sizeof = sizeof(Rectangle2D) * length_msg;
  Rectangle2D* const array_context_position = (Rectangle2D*)malloc(rectangle_2D_sizeof);
  size_t i;
  const float width = graphics_text_square_vertices_width(scale);
  for (i = 0; i < length_msg; ++i, position.x += width) {
    graphics_text_text_rectangle_2D(array_context_position + i, scale, position);
  }

  Rectangle2D* const array_texture_position = (Rectangle2D*)malloc(rectangle_2D_sizeof);
  for (i = 0; i < length_msg; ++i) {
    graphics_text_text_rectangle_2D_texture(array_texture_position + i, msg[i]);
  }

  graphics_primitive_rectangle_2D_draw(graphics_text->tbo_texture_tileset,
                                    array_context_position,
                                    array_texture_position,
                                    length_msg);

  free(array_context_position);
  free(array_texture_position);
}

#ifdef INCLUDE_RUN_TEST
static GraphicsText* graphics_text_graphics_text = 0x0;

//--------------------------------------------------------------------------------
static void graphics_text_draw_callback()
{
  if (!graphics_text_graphics_text) {
    graphics_text_graphics_text = graphics_text_calloc();
    assert(graphics_text_graphics_text);
  } else {
    const float scale = 1.0f;
    const GraphicsPoint2D position = {0.1, 0.5};
    graphics_text_draw(graphics_text_graphics_text, scale, position, "test");
  }
}

//--------------------------------------------------------------------------------
static void graphics_text_uninit_callback()
{
  assert(graphics_text_graphics_text);
  graphics_text_free(graphics_text_graphics_text);
  graphics_text_graphics_text = 0x0;
}

//--------------------------------------------------------------------------------
size_t graphics_text_run_test(void (** draw_callback)(void),
                              void (** uninit_callback)(void)) {
  {  // Set draw and uninit callback
    if (!draw_callback) {
      TEST_ASSERT_MSG("!draw_callback");
      return 1;
    }
    if (!uninit_callback) {
      TEST_ASSERT_MSG("!uninit_callback");
      return 1;
    }
    *draw_callback = &graphics_text_draw_callback;
    *uninit_callback = &graphics_text_uninit_callback;
  }

  {  // Test graphics_text_char_to_grid_coord
    GridCoord16x16 coord = graphics_text_char_to_grid_coord((char)0);
    TEST_ASSERT_TRUE(coord.x == 0);
    TEST_ASSERT_TRUE(coord.y == 0);

    coord = graphics_text_char_to_grid_coord((char)16);
    TEST_ASSERT_TRUE(coord.x == 0);
    TEST_ASSERT_TRUE(coord.y == 1);

    // Overflow
    coord = graphics_text_char_to_grid_coord((char)256);
    TEST_ASSERT_TRUE(coord.x == 0);
    TEST_ASSERT_TRUE(coord.y == 0);

    coord = graphics_text_char_to_grid_coord((char)34);
    TEST_ASSERT_TRUE(coord.x == 2);
    TEST_ASSERT_TRUE(coord.y == 2);
  }

  return 0;
}
#endif  // INCLUDE_RUN_TEST
