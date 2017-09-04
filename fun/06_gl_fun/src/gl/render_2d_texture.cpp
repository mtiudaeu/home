#include "gl/render_2d_texture.h"

#include "gl/shader.h"

#include <memory>

namespace {
struct Imp {
  ~Imp();

  GLuint m_program_id = 0;

  GLuint m_vbo_vertices_coord = 0;
  GLint m_attribute_vertices_coord = 0;

  GLint m_uniform_texture_tileset = 0;
  GLuint m_vbo_texture_coord = 0;
  GLint m_attribute_texture_coord = 0;
};
static std::unique_ptr<Imp> m_Imp;

Imp::~Imp() {
  glDeleteProgram(m_program_id);
  m_program_id = 0;

  glDeleteBuffers(1, &m_vbo_vertices_coord);
  m_vbo_vertices_coord = 0;

  glDeleteBuffers(1, &m_vbo_texture_coord);
  m_vbo_texture_coord = 0;
}

GLuint program_create() {
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

void set_vertices_data(
    GLuint vbo_vertices, GLint attribute_vertices,
    const struct triangle_vertex_2d_s* const triangles_vertices,
    const size_t vertices_sizeof) {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
  glBufferData(GL_ARRAY_BUFFER, vertices_sizeof, triangles_vertices,
               GL_STATIC_DRAW);

  glEnableVertexAttribArray(attribute_vertices);
  glVertexAttribPointer(
      attribute_vertices,  // attribute
      2,                   // number of elements per vertex,
      GL_FLOAT,            // the type of each element
      GL_FALSE,            // take our values as-is
      0,                   // no extra size
      0  // offset (GLvoid*)offsetof(struct <struct_name>, <member_name>)
      );
}

void draw_textures_vertices(const drawing_data_2d_s& drawing_data_2d) {

  glUseProgram(m_Imp->m_program_id);

  for (const auto& it : drawing_data_2d.texture_vertices_2d) {
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(m_Imp->m_uniform_texture_tileset,
                0  // GL_TEXTURE
                );
    glBindTexture(GL_TEXTURE_2D, it.bo_texture);

    const size_t vertices_sizeof =
        sizeof(struct triangle_vertex_2d_s) * it.length_triangles;
    set_vertices_data(m_Imp->m_vbo_vertices_coord, m_Imp->m_attribute_vertices_coord,
                      it.pos_triangles_vertices, vertices_sizeof);
    set_vertices_data(m_Imp->m_vbo_texture_coord, m_Imp->m_attribute_texture_coord,
                      it.texture_triangles_vertices, vertices_sizeof);

    glDrawArrays(GL_TRIANGLES, 0, 3 * it.length_triangles);

    glDisableVertexAttribArray(m_Imp->m_attribute_vertices_coord);
    glDisableVertexAttribArray(m_Imp->m_attribute_texture_coord);
  }
}
}

Status gl_render_2d_init() {
  Status status;

  m_Imp.reset(new Imp());

  m_Imp->m_program_id = program_create();
  if (!m_Imp->m_program_id) {
    status = BUILD_ERROR("!m_Imp->m_program_id");
    return status;
  }

  const char* uniform_name = "texture_tileset";
  m_Imp->m_uniform_texture_tileset =
      glGetUniformLocation(m_Imp->m_program_id, uniform_name);
  if (m_Imp->m_uniform_texture_tileset == -1) {
    status = BUILD_ERROR("glGetUniformLocation %s", uniform_name);
    return status;
  }

  {  // Create vertices objects

    const char* attribute_name = "vertices_coord";
    m_Imp->m_attribute_vertices_coord =
        glGetAttribLocation(m_Imp->m_program_id, attribute_name);
    if (m_Imp->m_attribute_vertices_coord == -1) {
      status = BUILD_ERROR("glGetAttribLocation %s", attribute_name);
      return status;
    }
  }

  {  // Create texture coord objects
    glGenBuffers(1, &m_Imp->m_vbo_texture_coord);

    const char* attribute_name = "texture_coord";
    m_Imp->m_attribute_texture_coord =
        glGetAttribLocation(m_Imp->m_program_id, attribute_name);
    if (m_Imp->m_attribute_texture_coord == -1) {
      status = BUILD_ERROR("glGetAttribLocation %s", attribute_name);
      return status;
    }
  }

  return status;
}

Status gl_render_2d() {
  //MDTMP LOG_DEBUG("gl_render_2d");

  drawing_data_2d_s* drawing_data_2d = &gl_render_2d_get_data();
  draw_textures_vertices(*drawing_data_2d);

  return Status();
}

drawing_data_2d_s& gl_render_2d_get_data()
{
  static drawing_data_2d_s data;
  return data;
}
