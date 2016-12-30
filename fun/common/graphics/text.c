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
  GLuint tbo_texture_map;
  GLuint uniform_texture_map;
  GLuint vbo_vertices_coord;
  GLint attribute_vertices_coord;
  GLuint vbo_texture_coord;
  GLint attribute_texture_coord;
};

typedef struct { // (-1.0,-1.0) is bottom left;
GLfloat bottom_left_1[2];
GLfloat top_right_1[2];
GLfloat top_left_1[2];
GLfloat bottom_left_2[2];
GLfloat top_right_2[2];
GLfloat bottom_right_2[2];
} SquareVertices;

typedef struct { // (0,0) is top left
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

    glGenTextures(1, &graphics_text->tbo_texture_map);
    glBindTexture(GL_TEXTURE_2D, graphics_text->tbo_texture_map);
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

    const char* uniform_name = "texture_map";
    graphics_text->uniform_texture_map =
        glGetUniformLocation(graphics_text->program, uniform_name);
    if (graphics_text->uniform_texture_map == -1) {
      LOG_ERROR("glGetUniformLocation %s", uniform_name);
      graphics_text_free(graphics_text);
      return 0x0;
    }
  }

  {  // Create vertices objects
    SquareVertices verticles_coord = {{-0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5},
                                     {-0.5, -0.5}, {0.5, 0.5}, {0.5, -0.5}};
    glGenBuffers(1, &graphics_text->vbo_vertices_coord);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_vertices_coord);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticles_coord), &verticles_coord,
                 GL_STATIC_DRAW);

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
    SquareVertices texture_coord = {{0.0, 0.0}, {1.0, 1.0}, {0.0, 1.0},
                                   {0.0, 0.0}, {1.0, 1.0}, {1.0, 0.0}};
//MDTMP
/*
    GLfloat texture_coord[6][2] = {{1.0-0.0625, 1.0-0.0625}, {1.0, 1.0}, {1.0-0.0625, 1.0},
                                   {1.0-0.0625, 1.0-0.0625}, {1.0, 1.0}, {1.0, 1.0-0.0625}};
*/
    glGenBuffers(1, &graphics_text->vbo_texture_coord);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_texture_coord);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coord), &texture_coord,
                 GL_STATIC_DRAW);

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
  glDeleteTextures(1, &graphics_text->uniform_texture_map);
  glDeleteBuffers(1, &graphics_text->vbo_vertices_coord);
  glDeleteBuffers(1, &graphics_text->vbo_texture_coord);

  free(graphics_text);
}

//--------------------------------------------------------------------------------
void graphics_text_draw(GraphicsText* graphics_text) {
  assert(graphics_text);

  glUseProgram(graphics_text->program);

  glActiveTexture(GL_TEXTURE0);
  glUniform1i(graphics_text->uniform_texture_map, /*GL_TEXTURE*/ 0);
  glBindTexture(GL_TEXTURE_2D, graphics_text->tbo_texture_map);

  glEnableVertexAttribArray(graphics_text->attribute_vertices_coord);
  glEnableVertexAttribArray(graphics_text->attribute_texture_coord);

  glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_vertices_coord);
  glVertexAttribPointer(
      graphics_text->attribute_vertices_coord,  // attribute
      2,         // number of elements per vertex,
      GL_FLOAT,  // the type of each element
      GL_FALSE,  // take our values as-is
      0,         // no extra size
      0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
      );

  glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_texture_coord);
  glVertexAttribPointer(
      graphics_text->attribute_texture_coord,  // attribute
      2,                                       // number of elements per vertex,
      GL_FLOAT,                                // the type of each element
      GL_FALSE,                                // take our values as-is
      0,                                       // no extra size
      0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
      );

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

  { // Test internal_char_to_grid_coord
    GridCoord16x16 coord = internal_char_to_grid_coord( (char)0 );
    TEST_ASSERT_EQUAL_UINT(coord.x, 0);
    TEST_ASSERT_EQUAL_UINT(coord.y, 0);

    coord = internal_char_to_grid_coord( (char)16 );
    TEST_ASSERT_EQUAL_UINT(coord.x, 0);
    TEST_ASSERT_EQUAL_UINT(coord.y, 1);

    // Overflow
    coord = internal_char_to_grid_coord( (char)256 );
    TEST_ASSERT_EQUAL_UINT(coord.x, 0);
    TEST_ASSERT_EQUAL_UINT(coord.y, 0);

    coord = internal_char_to_grid_coord( (char)34 );
    TEST_ASSERT_EQUAL_UINT(coord.x, 2);
    TEST_ASSERT_EQUAL_UINT(coord.y, 2);
  }


//MDTMP Coordinate coord = internal_translate_char_to_coord();

  return 0;
}
#endif  // INCLUDE_RUN_TEST
