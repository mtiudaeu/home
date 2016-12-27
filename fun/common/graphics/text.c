#include "graphics/text.h"

#include "test/test.h"

#include "log.h"

#include "SDL2/SDL_image.h"

#include <stdlib.h>
#include <assert.h>

//--------------------------------------------------------------------------------
GraphicsText* graphics_text_from_tileset_malloc(const char* filename) {
  SDL_Surface* tileset_texture = IMG_Load(filename);
  {  // Validate inputs
    if (!tileset_texture) {
      LOG_ERROR("IMG_Load: %s", SDL_GetError());
      return 0x0;
    }
    if (!tileset_texture->format) {
      LOG_ERROR("tileset_texture->format");
      return 0x0;
    }
    if (tileset_texture->format->BytesPerPixel != 3) {
      LOG_ERROR("tileset_texture->format->BytesPerPixel != 3");
      return 0x0;
    }
  }

  { // Create text object
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

    GraphicsText* graphics_text = malloc(sizeof(GraphicsText));
    graphics_text->texture_id = texture_id;

    return graphics_text;
  }
}

//--------------------------------------------------------------------------------
void graphics_text_free(GraphicsText* graphics_text) {
  assert(graphics_text);
  glDeleteTextures(1, &graphics_text->texture_id);
  free(graphics_text);
}

#ifdef INCLUDE_RUN_TEST
//--------------------------------------------------------------------------------
size_t graphics_text_test_run() {
  GraphicsText* graphics_text = graphics_text_from_tileset_malloc(
      "test/assets/Cooz_curses_square_16x16.png");

  TEST_ASSERT_TRUE_PTR(graphics_text);
  graphics_text_free(graphics_text);
  graphics_text = 0x0;

  return 0;
}
#endif  // INCLUDE_RUN_TEST
