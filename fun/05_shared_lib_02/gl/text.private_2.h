void graphics_primitive_rectangle_2D_uninit();

struct rectangle_2d {
  float x; // Bottom left corner
  float y; // Bottom left corner
  float width;
  float height;
};

static GLuint graphics_primitive_rectangle_2D_program_id = 0;

static GLuint graphics_primitive_rectangle_2D_vbo_vertices_coord = 0;
static GLint graphics_primitive_rectangle_2D_attribute_vertices_coord = 0;

static GLint graphics_primitive_rectangle_2D_uniform_texture_tileset = 0;
static GLuint graphics_primitive_rectangle_2D_vbo_texture_coord = 0;
static GLint graphics_primitive_rectangle_2D_attribute_texture_coord = 0;

//--------------------------------------------------------------------------------
struct triangle_verticles_2d {  // (-1.0,-1.0) is bottom left;
  GLfloat coord_1[2];
  GLfloat coord_2[2];
  GLfloat coord_3[2];
};

//--------------------------------------------------------------------------------
void graphics_primitive_triangle_vertices_from_rectangle_2D(
    struct triangle_verticles_2d triangle_vertices[2], const struct rectangle_2d rectangle_2D) {
  const GLfloat x_left = rectangle_2D.x;
  const GLfloat x_right = rectangle_2D.x + rectangle_2D.width;
  const GLfloat y_bottom = rectangle_2D.y;
  const GLfloat y_top = rectangle_2D.y + rectangle_2D.height;

  // bottom left
  triangle_vertices[0].coord_1[0] = triangle_vertices[1].coord_1[0] = x_left;
  triangle_vertices[0].coord_1[1] = triangle_vertices[1].coord_1[1] = y_bottom;

  // top right
  triangle_vertices[0].coord_2[0] = triangle_vertices[1].coord_2[0] = x_right;
  triangle_vertices[0].coord_2[1] = triangle_vertices[1].coord_2[1] = y_top;

  // top left
  triangle_vertices[0].coord_3[0] = x_left;
  triangle_vertices[0].coord_3[1] = y_top;

  // bottom right
  triangle_vertices[1].coord_3[0] = x_right;
  triangle_vertices[1].coord_3[1] = y_bottom;
}

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

  return shader_program_create_str(vertex_source, fragment_source);
}

//--------------------------------------------------------------------------------
size_t graphics_primitive_rectangle_2D_init() {

//MDTMP
  //glEnable(GL_DEBUG_OUTPUT);


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



void draw_vertices(GLuint vbo_vertices,
                   GLint attribute_vertices,
                   const struct triangle_verticles_2d* const triangles_vertices,
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

//MDTMP
/*
void draw_textures_vertices(
    GLuint bo_texture,
    const struct triangle_verticles_2d* const pos_triangles_vertices,
    const struct triangle_verticles_2d* const texture_triangles_vertices,
    const size_t length) {
  // MDTMP
}
*/

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

    draw_vertices(graphics_primitive_rectangle_2D_vbo_vertices_coord,
                  graphics_primitive_rectangle_2D_attribute_vertices_coord,
                  array_triangle_vertices, vertices_sizeof);
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

    draw_vertices(graphics_primitive_rectangle_2D_vbo_texture_coord,
                  graphics_primitive_rectangle_2D_attribute_texture_coord,
                  array_texture_coord, vertices_sizeof);
  }

  glDrawArrays(GL_TRIANGLES, 0, 3 * length_triangles);

  glDisableVertexAttribArray(
      graphics_primitive_rectangle_2D_attribute_vertices_coord);
  glDisableVertexAttribArray(
      graphics_primitive_rectangle_2D_attribute_texture_coord);
}

static void func2() {
  static bool init = false;
  if (!init) {
    if (graphics_primitive_rectangle_2D_init() != 0) {
      // MDTMP log error?
      return;
    }
    init = true;
  }
}
