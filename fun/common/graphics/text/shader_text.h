#ifndef GRAPHICS_TEXT_SHADER_TEXT_H
#define GRAPHICS_TEXT_SHADER_TEXT_H

#include "common/graphics/shader.h"

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
#endif  // GRAPHICS_TEXT_SHADER_TEXT_H
