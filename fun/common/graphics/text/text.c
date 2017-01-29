#include "common/graphics/text/text.h"

#include "common/graphics/point.h"
#include "common/graphics/context.h"

#include "common/graphics/primitive/square_2D.h"
#include "common/graphics/shader.h"

#include "common/test/test.h"

#include "common/log.h"

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

  const size_t square_2D_sizeof = sizeof(Square2D) * length_msg;
  Square2D* const array_context_position = (Square2D*)malloc(square_2D_sizeof);
  size_t i;
  const float width = internal_square_vertices_half_width(scale) * 2.0f;
  for (i = 0; i < length_msg; ++i, position.x += width) {
    internal_text_square_2D(array_context_position + i, scale, position);
  }

  Square2D* const array_texture_position = (Square2D*)malloc(square_2D_sizeof);
  for (i = 0; i < length_msg; ++i) {
    internal_text_square_2D_texture(array_texture_position + i, msg[i]);
  }

  graphics_primitive_square_2D_draw(graphics_text->tbo_texture_tileset,
                                    array_context_position,
                                    array_texture_position,
                                    length_msg);

  free(array_context_position);
  free(array_texture_position);
}

#ifdef INCLUDE_RUN_TEST
static GraphicsText* internal_graphics_text = 0x0;

//--------------------------------------------------------------------------------
static void internal_draw_callback()
{
  if (!internal_graphics_text) {
    internal_graphics_text = graphics_text_calloc();
    TEST_ASSERT_TRUE_PTR(internal_graphics_text);
  } else {
    const float scale = 0.5f;
    const GraphicsPoint2D position = {0.1, 0.5};
    graphics_text_draw(internal_graphics_text, scale, position, "test");
  }
}

//--------------------------------------------------------------------------------
static void internal_uninit_callback()
{
  TEST_ASSERT_TRUE_PTR(internal_graphics_text);
  graphics_text_free(internal_graphics_text);
  internal_graphics_text = 0x0;
}

//--------------------------------------------------------------------------------
size_t graphics_text_run_test(void (** draw_callback)(void),
                              void (** uninit_callback)(void)) {
  {  // Set draw and uninit callback
    if (!draw_callback) {
      TEST_ASSERT_MSG("!draw_callback", 1);
      return 1;
    }
    if (!uninit_callback) {
      TEST_ASSERT_MSG("!uninit_callback", 1);
      return 1;
    }
    *draw_callback = &internal_draw_callback;
    *uninit_callback = &internal_uninit_callback;
  }

  {  // Test internal_char_to_grid_coord
    GridCoord16x16 coord = internal_char_to_grid_coord((char)0);
    TEST_ASSERT_EQUAL_UINT(coord.x, 0);
    TEST_ASSERT_EQUAL_UINT(coord.y, 0);

    coord = internal_char_to_grid_coord((char)16);
    TEST_ASSERT_EQUAL_UINT(coord.x, 0);
    TEST_ASSERT_EQUAL_UINT(coord.y, 1);

    // Overflow
    coord = internal_char_to_grid_coord((char)256);
    TEST_ASSERT_EQUAL_UINT(coord.x, 0);
    TEST_ASSERT_EQUAL_UINT(coord.y, 0);

    coord = internal_char_to_grid_coord((char)34);
    TEST_ASSERT_EQUAL_UINT(coord.x, 2);
    TEST_ASSERT_EQUAL_UINT(coord.y, 2);
  }

  return 0;
}
#endif  // INCLUDE_RUN_TEST
