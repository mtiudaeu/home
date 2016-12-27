#include "test/test.h"

// MDTMP Add all include and link.

GraphicsText* graphics_text_from_tileset_malloc(const char* filename) {
  SDL_Surface* tileset_texture = IMG_Load(filename);

  if (!tileset_texture) {
    // MDTMP log error
    // MDTMP cerr << "IMG_Load: " << SDL_GetError() << endl;
    return 0x0;
  }

  ASSERT_DEBUG(res_texture->format->BytesPerPixel == 3);

  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D,       // target
               0,                   // level, 0 = base, no minimap,
               GL_RGB,              // internalformat
               tileset_texture->w,  // width
               tileset_texture->h,  // height
               0,                   // border, always 0 in OpenGL ES
               GL_RGB,              // format
               GL_UNSIGNED_BYTE,    // type
               tileset_texture->pixels);
  SDL_FreeSurface(tileset_texture);

  GraphicsText* graphics_text = malloc(1, sizeof(GraphicsText));
  graphics_text->texture_id = texture_id;

  return graphics_text;
}

void graphics_text_free(GraphicsText* graphics_text) {
  glDeleteTextures(1, graphics_text->texture_id);
  free(graphics_text);
}

#ifdef INCLUDE_RUN_TEST
int graphics_text_test_run() {
  GraphicsText* graphics_text = graphics_text_from_tileset_malloc(
      "test/assets/Cooz_curses_square_16x16.png");

  TEST_ASSERT_TRUE(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

  return 0;
}
#endif  // INCLUDE_RUN_TEST
