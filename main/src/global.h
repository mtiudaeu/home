#ifndef GLOBAL_H
#define GLOBAL_H

struct SDL_Window;

struct GlobalContext {
  SDL_Window* window;
  int width;
  int height;
  bool visible;
  unsigned int time_current;
  float time_delta;
};

#endif

