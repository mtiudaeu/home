attribute vec2 vertices_coord;
attribute vec2 texture_coord;
varying vec2 f_texture_coord;

void main(void) {
  gl_Position = vec4(vertices_coord, 0.0, 1.0);
  f_texture_coord = texture_coord;
}
