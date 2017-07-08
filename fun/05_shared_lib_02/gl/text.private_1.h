static GLuint texture_tileset = 0;

static void func1() {
  if (texture_tileset == 0) {
    const char* tileset_filename = "assets/tileset.png";
    texture_tileset = shader_texture_buffer_create(tileset_filename);
    // MDTMP glDeleteTextures(1, &texture_tileset);
    if (!texture_tileset) {
      LOG_ERROR("!texture_tileset");
      return;
    }
  }
}
