#include "gl/shader.h"

#include "core/module_create.h"

#include <GL/glew.h>

#include <map>
#include <string>

MODULE_DEFAULT_INITIALIZE;

static status_s render_step_cb() {
  assert(data_manager);

  const char* tileset_filename = "assets/text/tileset.png";
  static GLuint texture_tileset = shader_texture_buffer_create(tileset_filename);
  //MDTMP glDeleteTextures(1, &texture_tileset);
  if (!texture_tileset) {
    LOG_ERROR("!texture_tileset");
    //MDTMP
    return status_s();
  }


  return status_s();
}

MODULE_EXPORT_STEP_CB(render_step_cb);
