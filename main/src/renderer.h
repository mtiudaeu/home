#ifndef RENDERER_H
#define RENDERER_H

namespace renderer {
void init();
void uninit();

void process_event(const SDL_Event& event);
void render();
}

#endif
