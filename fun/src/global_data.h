#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

struct global_data {
  int time_current = 0;
  int time_delta = 0;
};

//MDTMP
/*
global_graphics_context->time_current = SDL_GetTicks();
const float time_delta = (float)(global_graphics_context->time_current -
global_graphics_context->time_last) /
1000.0f;
global_graphics_context->time_last = global_graphics_context->time_current;
*/
#endif // GLOBAL_DATA_
