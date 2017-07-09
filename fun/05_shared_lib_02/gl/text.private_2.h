#include "data/drawing_data_2d.h"

struct rectangle_2d {
  float x; // Bottom left corner
  float y; // Bottom left corner
  float width;
  float height;
};


//--------------------------------------------------------------------------------
void graphics_primitive_triangle_vertices_from_rectangle_2D(
    struct triangle_vertex_2d_s triangle_vertices[2], const struct rectangle_2d rectangle_2D) {
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

void graphics_primitive_rectangle_2D_draw(
    GLuint bo_texture, const struct rectangle_2d* array_context_position,
    const struct rectangle_2d* array_texture_position, size_t square_length) {

  const size_t length_triangles = square_length * 2;
  const size_t vertices_sizeof =
      sizeof(struct triangle_vertex_2d_s) * length_triangles;

  // position
  struct triangle_vertex_2d_s* const array_triangle_vertices =
      (struct triangle_vertex_2d_s*)malloc(vertices_sizeof);
  {
    size_t i = 0;
    for (; i < length_triangles; i += 2) {
      graphics_primitive_triangle_vertices_from_rectangle_2D(
          array_triangle_vertices + i, array_context_position[i / 2]);
    }
  }

  // texture
  struct triangle_vertex_2d_s* const array_texture_coord =
      (struct triangle_vertex_2d_s*)malloc(vertices_sizeof);
  {
    size_t i = 0;
    for (; i < length_triangles; i += 2) {
      graphics_primitive_triangle_vertices_from_rectangle_2D(
          array_texture_coord + i, array_texture_position[i / 2]);
    }
  }

  texture_vertices_2d_s vertices{bo_texture, array_triangle_vertices,
                            array_texture_coord, length_triangles};
  drawing_data_2d_s* drawing_data_2d = DM_GET_DATA(*data_manager, drawing_data_2d_s, "drawing_data_2d"); 
  drawing_data_2d->texture_vertices_2d.push_back(vertices);

  // free
//MDTMP
/*
  free(array_triangle_vertices);
  free(array_texture_coord);
*/

}

static void func2() {
}
