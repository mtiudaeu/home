#include "gl/shader.h"

#include "data/drawing_data_2d.h"

#include "core/module_create.h"

#include <vector>

static data_manager_s* data_manager = 0x0;

static GLuint graphics_primitive_rectangle_2D_program_id = 0;

static GLuint graphics_primitive_rectangle_2D_vbo_vertices_coord = 0;
static GLint graphics_primitive_rectangle_2D_attribute_vertices_coord = 0;

static GLint graphics_primitive_rectangle_2D_uniform_texture_tileset = 0;
static GLuint graphics_primitive_rectangle_2D_vbo_texture_coord = 0;
static GLint graphics_primitive_rectangle_2D_attribute_texture_coord = 0;

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

  return shader_program_create_str(vertex_source, fragment_source);
}

static status_s render_2d_texture_uninit_cb() {
  glDeleteProgram(graphics_primitive_rectangle_2D_program_id);
  graphics_primitive_rectangle_2D_program_id = 0;

  glDeleteBuffers(1, &graphics_primitive_rectangle_2D_vbo_vertices_coord);
  graphics_primitive_rectangle_2D_vbo_vertices_coord = 0;

  glDeleteBuffers(1, &graphics_primitive_rectangle_2D_vbo_texture_coord);
  graphics_primitive_rectangle_2D_vbo_texture_coord = 0;

  return status_s();
}

static status_s render_2d_texture_init_cb(data_manager_s* data) {
  data_manager = data;

  status_s status;
  if (graphics_primitive_rectangle_2D_program_id) {
    LOG_ERROR(
        "graphics_primitive_rectangle_2Dprogram_init : already initialized");
    status.error = true;
    return status;
  }

  graphics_primitive_rectangle_2D_program_id =
      graphics_primitive_rectangle_2D_program_create();
  if (!graphics_primitive_rectangle_2D_program_id) {
    LOG_ERROR("!graphics_primitive_rectangle_2Dprogram_init");
    status.error = true;
    return status;
  }

  const char* uniform_name = "texture_tileset";
  graphics_primitive_rectangle_2D_uniform_texture_tileset = glGetUniformLocation(
      graphics_primitive_rectangle_2D_program_id, uniform_name);
  if (graphics_primitive_rectangle_2D_uniform_texture_tileset == -1) {
    LOG_ERROR("glGetUniformLocation %s", uniform_name);
    render_2d_texture_uninit_cb();
    status.error = true;
    return status;
  }

  {  // Create vertices objects
    glGenBuffers(1, &graphics_primitive_rectangle_2D_vbo_vertices_coord);

    const char* attribute_name = "vertices_coord";
    graphics_primitive_rectangle_2D_attribute_vertices_coord =
        glGetAttribLocation(graphics_primitive_rectangle_2D_program_id,
                            attribute_name);
    if (graphics_primitive_rectangle_2D_attribute_vertices_coord == -1) {
      LOG_ERROR("glGetAttribLocation %s", attribute_name);
      render_2d_texture_uninit_cb();
      status.error = true;
      return status;
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
      render_2d_texture_uninit_cb();
      status.error = true;
      return status;
    }
  }

  return status;
}


void set_vertices_data(GLuint vbo_vertices,
                   GLint attribute_vertices,
                   const struct triangle_vertex_2d_s* const triangles_vertices,
                   const size_t vertices_sizeof) {
  glBindBuffer(GL_ARRAY_BUFFER,
               vbo_vertices);
  glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, triangles_vertices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(
      attribute_vertices);
  glVertexAttribPointer(
      attribute_vertices,  // attribute
      2,         // number of elements per vertex,
      GL_FLOAT,  // the type of each element
      GL_FALSE,  // take our values as-is
      0,         // no extra size
      0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
      );
}

void draw_textures_vertices(const drawing_data_2d_s& drawing_data_2d) {
  assert(graphics_primitive_rectangle_2D_program_id);
  glUseProgram(graphics_primitive_rectangle_2D_program_id);

  for (const auto& it : drawing_data_2d.texture_vertices_2d) {
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(graphics_primitive_rectangle_2D_uniform_texture_tileset,
                0  // GL_TEXTURE
                );
    glBindTexture(GL_TEXTURE_2D, it.bo_texture);

    const size_t vertices_sizeof =
        sizeof(struct triangle_vertex_2d_s) * it.length_triangles;
    set_vertices_data(graphics_primitive_rectangle_2D_vbo_vertices_coord,
                      graphics_primitive_rectangle_2D_attribute_vertices_coord,
                      it.pos_triangles_vertices, vertices_sizeof);
    set_vertices_data(graphics_primitive_rectangle_2D_vbo_texture_coord,
                      graphics_primitive_rectangle_2D_attribute_texture_coord,
                      it.texture_triangles_vertices, vertices_sizeof);

    glDrawArrays(GL_TRIANGLES, 0, 3 * it.length_triangles);

    glDisableVertexAttribArray(
        graphics_primitive_rectangle_2D_attribute_vertices_coord);
    glDisableVertexAttribArray(
        graphics_primitive_rectangle_2D_attribute_texture_coord);
  }
}

static status_s render_2d_texture_step_cb()
{
  LOG_DEBUG("render_2d_texture_step_cb");

  drawing_data_2d_s* drawing_data_2d = DM_GET_DATA(*data_manager, drawing_data_2d_s, "drawing_data_2d"); 
  draw_textures_vertices(*drawing_data_2d);

  return status_s();
}

MODULE_EXPORT(render_2d_texture_init_cb, render_2d_texture_uninit_cb, render_2d_texture_step_cb);
