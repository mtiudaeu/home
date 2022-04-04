#include "graphic/context.h"

#include "common/log.h"

#include <GL/glew.h>

static void handle_hotkey_cb(SDL_Event*ev) {
 if(ev->type == SDL_KEYDOWN) {
  switch(ev->key.keysym.sym) {
   case SDLK_LEFT:
   break;
  }
 } 
}

static void main_loop(const float time_delta_ms) {
 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 glEnable(GL_BLEND);

 glClearColor(0.0, 0.0, 0.0, 1.0);
 glClear(GL_COLOR_BUFFER_BIT);
 
}

int main() {
 size_t ret = graphic_context_global_init();
 if(ret != 0) {
  LOG_ERROR("graphic_context_global_init");
  return ret;;
 }

 graphic_context_global_run(&main_loop, &handle_hotkey_cb);

 ret = graphic_context_global_uninit();
 if(ret != 0) {
  LOG_ERROR("graphic_context_global_uninit");
  return ret;;
 }
}

