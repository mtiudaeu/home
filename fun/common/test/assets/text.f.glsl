varying vec2 f_texture_coord;
uniform sampler2D texture_map;

void main(void) {
  vec2 flipped_texture_coord = vec2(f_texture_coord.x, 1.0 - f_texture_coord.y);
  gl_FragColor = texture2D(texture_map, flipped_texture_coord);
}
