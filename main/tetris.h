#ifndef TETRIS_H
#define TETRIS_H

#include "render-layer.h"

#include <memory>

struct SDL_Window;
union SDL_Event;

struct TetrisImpl;

class Tetris: public IRenderLayer {
public:
  void Render(SDL_Window* window, bool reset, float time_delta);
  void ProcessEvent(SDL_Event* event);
  Tetris();
  ~Tetris();

private:
  std::unique_ptr<TetrisImpl> self;
};


#endif
