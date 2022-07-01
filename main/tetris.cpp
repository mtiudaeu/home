#include "glwrappers.h"
#include "tetris.h"

#include  <SDL.h>

struct TetrisImpl {
};

Tetris::Tetris() : self(new TetrisImpl()) {
}
Tetris::~Tetris() {
}

static unsigned int compile_shader(unsigned int type, const std::string& source) {
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*) alloca(length* sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    LOG_ERROR("Failed to compile shader!");
    LOG_ERROR("%s", message);
    glDeleteShader(id);
    return 0;
  }
  return id;
}

void Tetris::Render(SDL_Window* window, bool reset, float time_delta) {
 
  int w, h; 
  SDL_GetWindowSize(window, &w, &h);
  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

  // Clear screen
  //SDL_SetRenderDrawColor(screenSurface, 0xFF, 0xFF, 0xFF, 0xFF);
  //SDL_Clear(screenSurface);
  // Render red filled quad
  SDL_Rect fillRect = {w / 4, h / 4, w / 2,
                       h / 2};
  //SDL_SetDrawColor(screenSurface, 0xFF, 0x00, 0x00, 0xFF);
  SDL_FillRect(screenSurface, &fillRect, SDL_MapRGB(screenSurface->format, 255, 0, 0) );
}

void Tetris::ProcessEvent(SDL_Event* event) {
}

