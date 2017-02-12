#include "common/graphics/primitive/rectangle_2D.h"

#include "common/graphics/shader.h"

#include "common/test/test.h"

#include "common/log/log.h"

#include <assert.h>
#include <stdlib.h>

#include "common/graphics/primitive/rectangle_2D.private.h"

//--------------------------------------------------------------------------------
// static members
//MDTMP remove singleton, at least group in a struct.
static GLuint graphics_primitive_rectangle_2D_program_id = 0;

static GLuint graphics_primitive_rectangle_2D_vbo_vertices_coord = 0;
static GLint graphics_primitive_rectangle_2D_attribute_vertices_coord = 0;

static GLuint graphics_primitive_rectangle_2D_uniform_texture_tileset;
static GLuint graphics_primitive_rectangle_2D_vbo_texture_coord = 0;
static GLint graphics_primitive_rectangle_2D_attribute_texture_coord = 0;

//--------------------------------------------------------------------------------
static GLuint graphics_primitive_rectangle_2D_program_create() {
  const char vertex_source[] =
      "attribute vec2 vertices_coord;\
attribute vec2 texture_coord;\
varying vec2 f_texture_coord;\
\
void main(void) {\
  gl_Position = vec4(vertices_coord, 0.0, 1.0);\
  f_texture_coord = texture_coord;\
}";

  const char fragment_source[] =
      "varying vec2 f_texture_coord;\
uniform sampler2D texture_tileset;\
\
void main(void) {\
  vec2 flipped_texture_coord = vec2(f_texture_coord.x, 1.0 - f_texture_coord.y);\
  gl_FragColor = texture2D(texture_tileset, flipped_texture_coord);\
}";

  return graphics_shader_program_create_str(vertex_source, fragment_source);
}

//--------------------------------------------------------------------------------
size_t graphics_primitive_rectangle_2D_init() {
  if (graphics_primitive_rectangle_2D_program_id) {
    LOG_ERROR(
        "graphics_primitive_rectangle_2Dprogram_init : already initialized");
    return 1;
  }

  graphics_primitive_rectangle_2D_program_id =
      graphics_primitive_rectangle_2D_program_create();
  if (!graphics_primitive_rectangle_2D_program_id) {
    LOG_ERROR("!graphics_primitive_rectangle_2Dprogram_init");
    return 1;
  }

  const char* uniform_name = "texture_tileset";
  graphics_primitive_rectangle_2D_uniform_texture_tileset = glGetUniformLocation(
      graphics_primitive_rectangle_2D_program_id, uniform_name);
  if (graphics_primitive_rectangle_2D_uniform_texture_tileset == -1) {
    LOG_ERROR("glGetUniformLocation %s", uniform_name);
    graphics_primitive_rectangle_2D_uninit();
    return 1;
  }

  {  // Create vertices objects
    glGenBuffers(1, &graphics_primitive_rectangle_2D_vbo_vertices_coord);

    const char* attribute_name = "vertices_coord";
    graphics_primitive_rectangle_2D_attribute_vertices_coord =
        glGetAttribLocation(graphics_primitive_rectangle_2D_program_id,
                            attribute_name);
    if (graphics_primitive_rectangle_2D_attribute_vertices_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      graphics_primitive_rectangle_2D_uninit();
      return 1;
    }
  }

  {  // Create texture coord objects
    glGenBuffers(1, &graphics_primitive_rectangle_2D_vbo_texture_coord);

    const char* attribute_name = "texture_coord";
    graphics_primitive_rectangle_2D_attribute_texture_coord =
        glGetAttribLocation(graphics_primitive_rectangle_2D_program_id,
                            attribute_name);
    if (graphics_primitive_rectangle_2D_attribute_texture_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      graphics_primitive_rectangle_2D_uninit();
      return 1;
    }
  }

  return 0;
}

//--------------------------------------------------------------------------------
void graphics_primitive_rectangle_2D_uninit() {
  glDeleteProgram(graphics_primitive_rectangle_2D_program_id);
  graphics_primitive_rectangle_2D_program_id = 0;

  glDeleteBuffers(1, &graphics_primitive_rectangle_2D_vbo_vertices_coord);
  graphics_primitive_rectangle_2D_vbo_vertices_coord = 0;

  glDeleteBuffers(1, &graphics_primitive_rectangle_2D_vbo_texture_coord);
  graphics_primitive_rectangle_2D_vbo_texture_coord = 0;
}

//--------------------------------------------------------------------------------
void graphics_primitive_rectangle_2D_draw(
    GLuint bo_texture, const struct rectangle_2d* array_context_position,
    const struct rectangle_2d* array_texture_position, size_t square_length) {
  assert(graphics_primitive_rectangle_2D_program_id);

  {  // Bind program and text texture
    glUseProgram(graphics_primitive_rectangle_2D_program_id);

    glActiveTexture(GL_TEXTURE0);

    glUniform1i(graphics_primitive_rectangle_2D_uniform_texture_tileset,
                /*GL_TEXTURE*/ 0);
    glBindTexture(GL_TEXTURE_2D, bo_texture);
  }

  const size_t length_triangles = square_length * 2;
  {  // Set geometry position
    const size_t vertices_sizeof =
        sizeof(struct triangle_verticles_2d) * length_triangles;
    struct triangle_verticles_2d* const array_triangle_vertices =
        (struct triangle_verticles_2d*)malloc(vertices_sizeof);
    size_t i = 0;
    for (; i < length_triangles; i += 2) {
      graphics_primitive_triangle_vertices_from_rectangle_2D(
          array_triangle_vertices + i, array_context_position[i / 2]);
    }

    glBindBuffer(GL_ARRAY_BUFFER,
                 graphics_primitive_rectangle_2D_vbo_vertices_coord);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, array_triangle_vertices,
                 GL_STATIC_DRAW);
    free(array_triangle_vertices);

    glEnableVertexAttribArray(
        graphics_primitive_rectangle_2D_attribute_vertices_coord);
    glVertexAttribPointer(
        graphics_primitive_rectangle_2D_attribute_vertices_coord,  // attribute
        2,         // number of elements per vertex,
        GL_FLOAT,  // the type of each element
        GL_FALSE,  // take our values as-is
        0,         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }

  {  // Set texture vertices
    const size_t vertices_sizeof =
        sizeof(struct triangle_verticles_2d) * length_triangles;
    struct triangle_verticles_2d* const array_texture_coord =
        (struct triangle_verticles_2d*)malloc(vertices_sizeof);
    size_t i = 0;
    for (; i < length_triangles; i += 2) {
      graphics_primitive_triangle_vertices_from_rectangle_2D(
          array_texture_coord + i, array_texture_position[i / 2]);
    }

    glBindBuffer(GL_ARRAY_BUFFER,
                 graphics_primitive_rectangle_2D_vbo_texture_coord);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, array_texture_coord,
                 GL_STATIC_DRAW);
    free(array_texture_coord);

    glEnableVertexAttribArray(
        graphics_primitive_rectangle_2D_attribute_texture_coord);
    glVertexAttribPointer(
        graphics_primitive_rectangle_2D_attribute_texture_coord,  // attribute
        2,         // number of elements per vertex,
        GL_FLOAT,  // the type of each element
        GL_FALSE,  // take our values as-is
        0,         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }

  glDrawArrays(GL_TRIANGLES, 0, 3 * length_triangles);

  glDisableVertexAttribArray(
      graphics_primitive_rectangle_2D_attribute_vertices_coord);
  glDisableVertexAttribArray(
      graphics_primitive_rectangle_2D_attribute_texture_coord);
}

#ifdef INCLUDE_RUN_TEST
static GLuint graphics_primitive_rectangle_2Dbo_texture = 0;

//--------------------------------------------------------------------------------
size_t test_graphics_primitive_rectangle_2D_init() {
  assert(graphics_primitive_rectangle_2D_init() == 0);
  const char* tileset_filename = "common/assets/tmp/tetris.png";
  graphics_primitive_rectangle_2Dbo_texture =
      graphics_shader_texture_buffer_create(tileset_filename);
  assert(graphics_primitive_rectangle_2Dbo_texture);

  return 0;
}

//--------------------------------------------------------------------------------
size_t test_graphics_primitive_rectangle_2D_uninit() {
  glDeleteTextures(1, &graphics_primitive_rectangle_2Dbo_texture);
  graphics_primitive_rectangle_2D_uninit();

  return 0;
}

//--------------------------------------------------------------------------------
void test_graphics_primitive_rectangle_2D_draw() {
  struct rectangle_2d rectangle_2D;
  rectangle_2D.x = -0.2f;
  rectangle_2D.y = -0.2f;
  rectangle_2D.width = 0.2f;
  rectangle_2D.height = 0.2f;

  struct rectangle_2d array_context_position[2];
  array_context_position[0] = rectangle_2D;
  rectangle_2D.y = 0.6f;
  array_context_position[1] = rectangle_2D;

  float texture_increment_x = 1.0f / 5.0f;
  float texture_increment_y = 1.0f / 2.0f;
  rectangle_2D.width = texture_increment_x;
  rectangle_2D.height = texture_increment_y;
  rectangle_2D.x = (1.0f * texture_increment_x);
  rectangle_2D.y = (3.0f * texture_increment_y);

  struct rectangle_2d array_texture_position[2];
  array_texture_position[0] = rectangle_2D;
  array_texture_position[1] = rectangle_2D;

  graphics_primitive_rectangle_2D_draw(
      graphics_primitive_rectangle_2Dbo_texture, array_context_position,
      array_texture_position, 2);
}

//--------------------------------------------------------------------------------
size_t test_graphics_primitive_rectangle_2D_run() {
  return 0;
}
#endif  // INCLUDE_RUN_TEST
