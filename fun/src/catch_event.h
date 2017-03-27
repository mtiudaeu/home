#ifndef CATCH_EVENT_H
#define CATCH_EVENT_H

#include <SDL2/SDL.h>

#include <vector>

struct catch_event {
  std::vector<SDL_Event> event_queue;
};

#endif // CATCH_EVENT_H

