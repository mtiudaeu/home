#ifndef GL_DRAWING_DATA_2D_H
#define GL_DRAWING_DATA_2D_H

#include <GL/glew.h>

#include <vector>

struct triangle_vertex_2d_s {  // (-1.0,-1.0) is bottom left;
  GLfloat coord_1[2];
  GLfloat coord_2[2];
  GLfloat coord_3[2];
};

struct texture_vertices_2d_s {
  GLuint bo_texture = 0;
  triangle_vertex_2d_s* pos_triangles_vertices = 0;
  triangle_vertex_2d_s* texture_triangles_vertices = 0;
  size_t length_triangles = 0;
};

struct drawing_data_2d_s {
  std::vector<texture_vertices_2d_s> texture_vertices_2d;
};

#endif

