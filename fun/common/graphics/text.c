#include "graphics/text.h"

#include "graphics/shader.h"

#include "test/test.h"

#include "log.h"

#include <GL/glew.h>
#include "SDL2/SDL_image.h"

#include <assert.h>
#include <stdlib.h>

struct GraphicsText {
  GLuint program;
  GLuint tbo_texture_tileset;
  GLuint uniform_texture_tileset;
  GLuint vbo_vertices_coord;
  GLint attribute_vertices_coord;
  GLuint vbo_texture_coord;
  GLint attribute_texture_coord;
};

typedef struct SquareVertices { // (-1.0,-1.0) is bottom left;
GLfloat bottom_left_1[2];
GLfloat top_right_1[2];
GLfloat top_left_1[2];
GLfloat bottom_left_2[2];
GLfloat top_right_2[2];
GLfloat bottom_right_2[2];
} SquareVertices;

// 0.0625 is 1/16
#define TEXTURE_CHARACTER_WIDTH 1.0f/16.0f
typedef struct SquareTexture { // (0.0,0.0) is bottom left;
GLfloat bottom_left_1[2];
GLfloat top_right_1[2];
GLfloat top_left_1[2];
GLfloat bottom_left_2[2];
GLfloat top_right_2[2];
GLfloat bottom_right_2[2];
} SquareTexture;

typedef struct GridCoord16x16 { // (0,0) is top left
  unsigned int x;
  unsigned int y;
} GridCoord16x16;

//--------------------------------------------------------------------------------
static GridCoord16x16 internal_char_to_grid_coord(char value)
{
  GridCoord16x16 coord;
  coord.x = value % 16; 
  coord.y = value / 16; 
  return coord;
}

//--------------------------------------------------------------------------------
static SquareTexture internal_create_square_vertices(GridCoord16x16 coord)
{
  const GLfloat x_left = (float)coord.x * TEXTURE_CHARACTER_WIDTH;
  const GLfloat x_right = x_left + TEXTURE_CHARACTER_WIDTH;
  const GLfloat y_top = 1.0f - (coord.y * TEXTURE_CHARACTER_WIDTH);
  const GLfloat y_bottom = y_top - TEXTURE_CHARACTER_WIDTH;

  SquareTexture square;
  square.bottom_left_1[0] = square.bottom_left_2[0] = x_left;
  square.bottom_left_1[1] = square.bottom_left_2[1] = y_bottom;

  square.top_right_1[0] = square.top_right_2[0] = x_right;
  square.top_right_1[1] = square.top_right_2[1] = y_top;

  square.top_left_1[0] = x_left;
  square.top_left_1[1] = y_top;

  square.bottom_right_2[0] = x_right;
  square.bottom_right_2[1] = y_bottom;
  return square;
}

//--------------------------------------------------------------------------------
static void internal_square_texture_set_value(SquareTexture* square_texture,
                                              char value) {
  assert(square_texture);
  //MDTMP add test
  //MDTMP unify those two in one... maybe not... unit testing...
  GridCoord16x16 character_coord = internal_char_to_grid_coord(value);
  SquareTexture texture_square =
      internal_create_square_vertices(character_coord);
  //MDTMP no copy?
  memcpy(square_texture, &texture_square, sizeof(texture_square));
}

//--------------------------------------------------------------------------------
//MDTMP
/*
void internal_square_vertices_set_value(SquareVertices* square_vertices,
                                        float scale, GraphicsPoint position) {
  assert(square_vertices);
  //MDTMP
}
*/

//--------------------------------------------------------------------------------
//MDTMP change name of calloc
GraphicsText* graphics_text_from_tileset_malloc(const char* filename) {
  GraphicsText* graphics_text = calloc(1, sizeof(GraphicsText));

  {  // Create shader
     // MDTMP remove hardcoded value..
    // MDTMP maybe hardcode actual sharder string here...
    graphics_text->program = graphics_shader_create_program(
        "test/assets/text.v.glsl", "test/assets/text.f.glsl");
    if (!graphics_text->program) {
      LOG_ERROR("graphics_shader_create_program");
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  {  // Create texture map objects
    SDL_Surface* tileset_texture = IMG_Load(filename);
    if (!tileset_texture) {
      LOG_ERROR("IMG_Load: %s", SDL_GetError());
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
//FIXME  Could accumulate all text to draw on screen and call glDrawArray once.
//MDTMP void graphics_text_draw(GraphicsText* graphics_text, float scale,
//MDTMP GraphicsPoint position, const char* msg) {
void graphics_text_draw(GraphicsText* graphics_text) {
  assert(graphics_text);

  { // Bind program and text texture
    glUseProgram(graphics_text->program);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(graphics_text->uniform_texture_tileset, /*GL_TEXTURE*/ 0);
    glBindTexture(GL_TEXTURE_2D, graphics_text->tbo_texture_tileset);
  }

//MDTMP const size_t length_msg = strlen(msg);
  const size_t length_msg = 1;
  {  // Set position vertices
    const size_t length_square_vertices = sizeof(SquareVertices) * length_msg;
    SquareVertices * const array_verticles_coord = malloc(length_square_vertices);
//MDTMP use custom malloc
    for (size_t i = 0; i < length_msg; ++i) {
      const SquareVertices verticles_coord = {{-0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5},
                                        {-0.5, -0.5}, {0.5, 0.5}, {0.5, -0.5}};
      memcpy(array_verticles_coord + i, &verticles_coord, sizeof(verticles_coord));
      //MDTMP internal_square_vertices_set_value(array_verticles_coord+i, scale, position);
    }

    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_vertices_coord);
    glBufferData(GL_ARRAY_BUFFER, length_square_vertices,
                 array_verticles_coord, GL_STATIC_DRAW);
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
//MDTMP use custom malloc
    SquareTexture * const array_texture_coord = malloc(length_square_texture);
    for (size_t i = 0; i < length_msg; ++i) {
      //MDTMP replace by msg[i]?
//MDTMP internal_square_texture_set_value(array_texture_coord+i, *(msg + i));
      internal_square_texture_set_value(array_texture_coord+i, 'a');
    }
    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_texture_coord);
    glBufferData(GL_ARRAY_BUFFER, length_square_texture,
                 array_texture_coord, GL_STATIC_DRAW);
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

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(graphics_text->attribute_vertices_coord);
  glDisableVertexAttribArray(graphics_text->attribute_texture_coord);
}

#ifdef INCLUDE_RUN_TEST
//--------------------------------------------------------------------------------
size_t graphics_text_run_test() {
  GraphicsText* graphics_text =
      graphics_text_from_tileset_malloc("test/assets/ASCII_tileset.png");

  TEST_ASSERT_TRUE_PTR(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

  {  // Test internal_char_to_grid_coord
//MDTMP add more test
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

  {  // Test internal_create_square_vertices
//MDTMP add more test
    GridCoord16x16 coord = {15, 0};
    SquareTexture answer = {
        {1.0 - 0.0625, 1.0 - 0.0625}, {1.0, 1.0}, {1.0 - 0.0625, 1.0},
        {1.0 - 0.0625, 1.0 - 0.0625}, {1.0, 1.0}, {1.0, 1.0 - 0.0625}};
    SquareTexture result = internal_create_square_vertices(coord);
    if (memcmp(&result, &answer, sizeof(result)) != 0) {
      TEST_ASSERT_MSG("internal_create_square_vertices");
    }
  }

  return 0;
}
#endif  // INCLUDE_RUN_TEST
