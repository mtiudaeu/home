#include "graphics/text/text.h"

#include "graphics/point.h"
#include "graphics/shader.h"

#include "test/test.h"

#include "log.h"

#include <GL/glew.h>
#include "SDL2/SDL_image.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "graphics/text/square_texture.h"
#include "graphics/text/square_vertices.h"

//--------------------------------------------------------------------------------
struct GraphicsText {
  GLuint program;
  GLuint tbo_texture_tileset;
  GLuint uniform_texture_tileset;
  GLuint vbo_vertices_coord;
  GLint attribute_vertices_coord;
  GLuint vbo_texture_coord;
  GLint attribute_texture_coord;
};

//--------------------------------------------------------------------------------
GraphicsText* graphics_text_from_tileset_calloc() {
  GraphicsText* graphics_text = calloc(1, sizeof(GraphicsText));

  {  // Create shader
    graphics_text->program = graphics_shader_program_create_file(
        "assets/text/texture.v.glsl", "assets/text/texture.f.glsl");
    if (!graphics_text->program) {
      LOG_ERROR("graphics_shader_program_create_file");
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  {  // Create texture map objects
    const char* tileset_filename = "assets/text/ASCII_tileset.png";
    SDL_Surface* tileset_texture = IMG_Load(tileset_filename);
    if (!tileset_texture) {
      LOG_ERROR("IMG_Load: %s : %s", SDL_GetError(), tileset_filename);
      graphics_text_free(graphics_text);
      return 0x0;
    }
    if (!tileset_texture->format) {
      LOG_ERROR("tileset_texture->format");
      graphics_text_free(graphics_text);
      return 0x0;
    }
    if (tileset_texture->format->BytesPerPixel != 4) {
      // This assumes GL_RGBA when calling glTexImage2D
      LOG_ERROR("tileset_texture->format->BytesPerPixel != 4");
      graphics_text_free(graphics_text);
      return 0x0;
    }

    glGenTextures(1, &graphics_text->tbo_texture_tileset);
    glBindTexture(GL_TEXTURE_2D, graphics_text->tbo_texture_tileset);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,       // target
                 0,                   // level, 0 = base, no minimap,
                 GL_RGBA,             // internalformat
                 tileset_texture->w,  // width
                 tileset_texture->h,  // height
                 0,                   // border, always 0 in OpenGL ES
                 GL_RGBA,             // format
                 GL_UNSIGNED_BYTE,    // type
                 tileset_texture->pixels);
    SDL_FreeSurface(tileset_texture);

    const char* uniform_name = "texture_tileset";
    graphics_text->uniform_texture_tileset =
        glGetUniformLocation(graphics_text->program, uniform_name);
    if (graphics_text->uniform_texture_tileset == -1) {
      LOG_ERROR("glGetUniformLocation %s", uniform_name);
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  {  // Create vertices objects
    glGenBuffers(1, &graphics_text->vbo_vertices_coord);

    const char* attribute_name = "vertices_coord";
    graphics_text->attribute_vertices_coord =
        glGetAttribLocation(graphics_text->program, attribute_name);
    if (graphics_text->attribute_vertices_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  {  // Create texture coord objects
    glGenBuffers(1, &graphics_text->vbo_texture_coord);

    const char* attribute_name = "texture_coord";
    graphics_text->attribute_texture_coord =
        glGetAttribLocation(graphics_text->program, attribute_name);
    if (graphics_text->attribute_texture_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  return graphics_text;
}

//--------------------------------------------------------------------------------
void graphics_text_free(GraphicsText* graphics_text) {
  assert(graphics_text);

  glDeleteProgram(graphics_text->program);
  glDeleteTextures(1, &graphics_text->tbo_texture_tileset);
  glDeleteBuffers(1, &graphics_text->vbo_vertices_coord);
  glDeleteBuffers(1, &graphics_text->vbo_texture_coord);

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

  {  // Bind program and text texture
    glUseProgram(graphics_text->program);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(graphics_text->uniform_texture_tileset, /*GL_TEXTURE*/ 0);
    glBindTexture(GL_TEXTURE_2D, graphics_text->tbo_texture_tileset);
  }

  const size_t length_msg = strlen(msg);
  {  // Set position vertices
    const size_t length_square_vertices = sizeof(SquareVertices) * length_msg;
    SquareVertices* const array_verticles_coord =
        (SquareVertices*)malloc(length_square_vertices);
    const float width = internal_square_vertices_half_width(scale) * 2.0f;
    position.x -= width;  // make sure i = 0 have correct value.
    for (size_t i = 0; i < length_msg; ++i) {
      position.x += width;
      internal_square_vertices_set_value(array_verticles_coord + i, scale,
                                         position);
    }

    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_vertices_coord);
    glBufferData(GL_ARRAY_BUFFER, length_square_vertices, array_verticles_coord,
                 GL_STATIC_DRAW);
    free(array_verticles_coord);

    glEnableVertexAttribArray(graphics_text->attribute_vertices_coord);
    glVertexAttribPointer(
        graphics_text->attribute_vertices_coord,  // attribute
        2,         // number of elements per vertex,
        GL_FLOAT,  // the type of each element
        GL_FALSE,  // take our values as-is
        0,         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }

  {  // Set texture vertices
    const size_t length_square_texture = sizeof(SquareTexture) * length_msg;
    SquareTexture* const array_texture_coord =
        (SquareTexture*)malloc(length_square_texture);
    for (size_t i = 0; i < length_msg; ++i) {
      internal_square_texture_set_value(array_texture_coord + i, msg[i]);
    }
    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_texture_coord);
    glBufferData(GL_ARRAY_BUFFER, length_square_texture, array_texture_coord,
                 GL_STATIC_DRAW);
    free(array_texture_coord);

    glEnableVertexAttribArray(graphics_text->attribute_texture_coord);
    glVertexAttribPointer(
        graphics_text->attribute_texture_coord,  // attribute
        2,         // number of elements per vertex,
        GL_FLOAT,  // the type of each element
        GL_FALSE,  // take our values as-is
        0,         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }

  glDrawArrays(GL_TRIANGLES, 0, 6 * length_msg);

  glDisableVertexAttribArray(graphics_text->attribute_vertices_coord);
  glDisableVertexAttribArray(graphics_text->attribute_texture_coord);
}

#ifdef INCLUDE_RUN_TEST
//--------------------------------------------------------------------------------
size_t graphics_text_run_test() {
  GraphicsText* graphics_text = graphics_text_from_tileset_calloc();

  TEST_ASSERT_TRUE_PTR(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

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

  {  // Test internal_square_texture_fill
    GridCoord16x16 coord = {15, 0};
    SquareTexture answer = {
        {1.0 - 0.0625, 1.0 - 0.0625}, {1.0, 1.0}, {1.0 - 0.0625, 1.0},
        {1.0 - 0.0625, 1.0 - 0.0625}, {1.0, 1.0}, {1.0, 1.0 - 0.0625}};
    SquareTexture result;
    internal_square_texture_fill(&result, coord);
    TEST_ASSERT_MSG("internal_square_texture_fill",
                    memcmp(&result, &answer, sizeof(result)) != 0);
  }

  return 0;
}
#endif  // INCLUDE_RUN_TEST
