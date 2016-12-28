#include "graphics/text.h"

#include "graphics/shader.h"

#include "test/test.h"

#include "log.h"

#include "SDL2/SDL_image.h"

#include <stdlib.h>
#include <assert.h>

//MDTMP remove! or change or rename.
struct attributes {
  GLfloat coord2d[2];
};

//--------------------------------------------------------------------------------
GraphicsText* graphics_text_from_tileset_malloc(const char* filename) {
  GraphicsText* graphics_text = calloc(1, sizeof(GraphicsText));

  {  // Create texture object
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
    if (tileset_texture->format->BytesPerPixel != 3) {
      LOG_ERROR("tileset_texture->format->BytesPerPixel != 3");
      graphics_text_free(graphics_text);
      return 0x0;
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,       // target
                 0,                   // level, 0 = base, no minimap,
                 GL_RGB,              // internalformat
                 tileset_texture->w,  // width
                 tileset_texture->h,  // height
                 0,                   // border, always 0 in OpenGL ES
                 GL_RGB,              // format
                 GL_UNSIGNED_BYTE,    // type
                 tileset_texture->pixels);
    SDL_FreeSurface(tileset_texture);

    graphics_text->texture_id = texture_id;
  }

  {  // Create shader
     // MDTMP remove hardcoded value..
    // MDTMP maybe hardcode actual sharder string here...
    GLuint program_id = graphics_shader_create_program(
        "test/assets/triangle.v.glsl", "test/assets/triangle.f.glsl");
    if (!program_id) {
      LOG_ERROR("graphics_shader_create_program");
      graphics_text_free(graphics_text);
      return 0x0;
    }
    graphics_text->program_id = program_id;
  }

  {  // Create vertex buffer
    struct attributes triangle_attributes[] =
 {
{{-0.5, -0.5}},
{{0.5, 0.5}},
{{-0.5, 0.5}},

{{-0.5, -0.5}},
{{0.5, 0.5}},
{{0.5, -0.5}}
};
    glGenBuffers(1, &graphics_text->vbo_triangle);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_triangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes),
                 triangle_attributes, GL_STATIC_DRAW);
  }

  {  // Create shader attributes.
    const char* attribute_name;
    attribute_name = "coord2d";
    graphics_text->attribute_coord2d =
        glGetAttribLocation(graphics_text->program_id, attribute_name);
    if (graphics_text->attribute_coord2d == -1) {
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

  glDeleteTextures(1, &graphics_text->texture_id);
  glDeleteProgram(graphics_text->program_id);
  glDeleteBuffers(1, &graphics_text->vbo_triangle);

  free(graphics_text);
}

//--------------------------------------------------------------------------------
void graphics_text_draw(GraphicsText* graphics_text)
{
  assert(graphics_text);

  glUseProgram(graphics_text->program_id);

  glEnableVertexAttribArray(graphics_text->attribute_coord2d);
  glBindBuffer(GL_ARRAY_BUFFER, graphics_text->vbo_triangle);
  glVertexAttribPointer(
      graphics_text->attribute_coord2d,          // attribute
      2,                          // number of elements per vertex,
      GL_FLOAT,                   // the type of each element
      GL_FALSE,                   // take our values as-is
      sizeof(struct attributes),  // size
      0                           // offset (GLvoid*)offsetof(struct attributes, v_color)
      );

//MDTMP number of points...
glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(graphics_text->attribute_coord2d);

}

#ifdef INCLUDE_RUN_TEST
//--------------------------------------------------------------------------------
size_t graphics_text_test_run() {
  GraphicsText* graphics_text = graphics_text_from_tileset_malloc(
      "test/assets/Cooz_curses_square_16x16.png");

  TEST_ASSERT_TRUE_PTR(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

  return 0;
}
#endif  // INCLUDE_RUN_TEST
