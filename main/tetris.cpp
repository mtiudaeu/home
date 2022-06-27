#include "tetris.h"

#include  <SDL.h>

struct TetrisImpl {
};

Tetris::Tetris() {
}
Tetris::~Tetris() {
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

