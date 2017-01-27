#include "common/graphics/primitive/square_2D.h"

#include "common/graphics/primitive/triangle_vertices_2D.h"

#include "common/graphics/shader.h"

#include "common/test/test.h"

#include "common/log.h"

#include <assert.h>
#include <stdlib.h>

static GLuint internal_program_id = 0;

//MDTMP rename with internal.
static GLuint vbo_vertices_coord = 0;
static GLint attribute_vertices_coord = 0;

static GLuint uniform_texture_tileset;
static GLuint vbo_texture_coord = 0;
static GLint attribute_texture_coord = 0;

//--------------------------------------------------------------------------------
static GLuint internal_program_create() {
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

/* MDTMP
//--------------------------------------------------------------------------------
void internal_square_2D_array_draw(
vbo_vertices
attribute
const Square2D* array_square,
                                   size_t square_length)
{
  const size_t length_triangles = square_length * 2;
  {  // Set geometry position
    const size_t vertices_sizeof =
        sizeof(TriangleVertices2D) * length_triangles;
    TriangleVertices2D* const array_triangle_vertices =
        (TriangleVertices2D*)malloc(vertices_sizeof);
    size_t i = 0;
    for (; i < length_triangles; i += 2) {
      graphics_primitive_triangle_vertices_from_square_2D(
          array_triangle_vertices + i, array_square[i / 2]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices_coord);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, array_triangle_vertices,
                 GL_STATIC_DRAW);
    free(array_triangle_vertices);

    glEnableVertexAttribArray(attribute_vertices_coord);
    glVertexAttribPointer(
        attribute_vertices_coord,  // attribute
        2,                         // number of elements per vertex,
        GL_FLOAT,                  // the type of each element
        GL_FALSE,                  // take our values as-is
        0,                         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }
}
*/


//--------------------------------------------------------------------------------
size_t graphics_primitive_square_2D_init() {
  if (internal_program_id) {
    LOG_ERROR("internal_program_init : already initialized");
    return 1;
  }

  internal_program_id = internal_program_create();
  if (!internal_program_id) {
    LOG_ERROR("!internal_program_init");
    return 1;
  }

  const char* uniform_name = "texture_tileset";
  uniform_texture_tileset =
      glGetUniformLocation(internal_program_id, uniform_name);
  if (uniform_texture_tileset == -1) {
    LOG_ERROR("glGetUniformLocation %s", uniform_name);
    graphics_primitive_square_2D_uninit();
    return 1;
  }

  {  // Create vertices objects
    glGenBuffers(1, &vbo_vertices_coord);

    const char* attribute_name = "vertices_coord";
    attribute_vertices_coord =
        glGetAttribLocation(internal_program_id, attribute_name);
    if (attribute_vertices_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      graphics_primitive_square_2D_uninit();
      return 1;
    }
  }

  {  // Create texture coord objects
    glGenBuffers(1, &vbo_texture_coord);

    const char* attribute_name = "texture_coord";
    attribute_texture_coord =
        glGetAttribLocation(internal_program_id, attribute_name);
    if (attribute_texture_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      graphics_primitive_square_2D_uninit();
      return 1;
    }
  }

  return 0;
}

//--------------------------------------------------------------------------------
void graphics_primitive_square_2D_uninit()
{
  glDeleteProgram(internal_program_id);
  internal_program_id = 0;

  glDeleteBuffers(1, &vbo_vertices_coord);
  vbo_vertices_coord = 0;

  glDeleteBuffers(1, &vbo_texture_coord);
  vbo_texture_coord = 0;
}

//--------------------------------------------------------------------------------
void graphics_primitive_square_2D_draw(GLuint bo_texture,
                                       const Square2D* array_context_position,
                                       const Square2D* array_texture_position,
                                       size_t square_length)
{
  assert(internal_program_id);

  {  // Bind program and text texture
    glUseProgram(internal_program_id);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(uniform_texture_tileset, /*GL_TEXTURE*/ 0);
    glBindTexture(GL_TEXTURE_2D, bo_texture);
  }

  const size_t length_triangles = square_length * 2;
  {  // Set geometry position
    const size_t vertices_sizeof = sizeof(TriangleVertices2D) * length_triangles;
    TriangleVertices2D* const array_triangle_vertices =
        (TriangleVertices2D*)malloc(vertices_sizeof);
    size_t i = 0;
    for (; i < length_triangles; i += 2) {
      graphics_primitive_triangle_vertices_from_square_2D(
          array_triangle_vertices + i, array_context_position[i / 2]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices_coord);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, array_triangle_vertices,
                 GL_STATIC_DRAW);
    free(array_triangle_vertices);

    glEnableVertexAttribArray(attribute_vertices_coord);
    glVertexAttribPointer(
        attribute_vertices_coord,  // attribute
        2,         // number of elements per vertex,
        GL_FLOAT,  // the type of each element
        GL_FALSE,  // take our values as-is
        0,         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }

  {  // Set texture vertices
    const size_t vertices_sizeof = sizeof(TriangleVertices2D) * length_triangles;
    TriangleVertices2D* const array_texture_coord =
        (TriangleVertices2D*)malloc(vertices_sizeof);
    size_t i = 0;
    for (; i < length_triangles; i+=2) {
      graphics_primitive_triangle_vertices_from_square_2D(
          array_texture_coord + i, array_texture_position[i / 2]);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_texture_coord);
    glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, array_texture_coord,
                 GL_STATIC_DRAW);
    free(array_texture_coord);

    glEnableVertexAttribArray(attribute_texture_coord);
    glVertexAttribPointer(
        attribute_texture_coord,  // attribute
        2,         // number of elements per vertex,
        GL_FLOAT,  // the type of each element
        GL_FALSE,  // take our values as-is
        0,         // no extra size
        0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
        );
  }

  glDrawArrays(GL_TRIANGLES, 0, 3 * length_triangles);

  glDisableVertexAttribArray(attribute_vertices_coord);
  glDisableVertexAttribArray(attribute_texture_coord);
}

#ifdef INCLUDE_RUN_TEST
static GLuint internal_bo_texture = 0;

//--------------------------------------------------------------------------------
static void internal_draw_callback() {
  if (!internal_bo_texture) {
    const char* tileset_filename = "common/assets/text/ASCII_tileset.png";
    internal_bo_texture =
        graphics_shader_texture_buffer_create(tileset_filename);
    if (!internal_bo_texture) {
      TEST_ASSERT_MSG("internal_bo_texture", 1)
    }
  }

  Square2D square_2D;
  square_2D.x = -0.2f;
  square_2D.y = -0.2f;
  square_2D.half_width = 0.2f;

  Square2D array_context_position[2];
  array_context_position[0] = square_2D;
  square_2D.y = 0.6f;
  array_context_position[1] = square_2D;

  square_2D.x = 0.5f;
  square_2D.y = 0.5f;
  square_2D.half_width = 0.5f;
  Square2D array_texture_position[2];
  array_texture_position[0] = square_2D;
  array_texture_position[1] = square_2D;

  graphics_primitive_square_2D_draw(internal_bo_texture, array_context_position,
                                    array_texture_position, 2);
}

//--------------------------------------------------------------------------------
static void internal_uninit_callback()
{
  glDeleteTextures(1, &internal_bo_texture);
}

//--------------------------------------------------------------------------------
size_t graphics_primitive_square_2D_run_test(void (** draw_callback)(void),
                                             void (** uninit_callback)(void))
{
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

  return 0;
}
#endif // INCLUDE_RUN_TEST

