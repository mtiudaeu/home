#ifndef SDL_SDL_WRAPPER_H
#define SDL_SDL_WRAPPER_H

class SDLWrapper {
  class Imp;
  Imp* m_imp;

 public:
  SDLWrapper();
  ~SDLWrapper();

  void swapBuffer() const;
  void catch_quit_event() const;
  // TODO
  //void queueEvents(SDL_Wrapper_Events&) const;

  SDLWrapper(const SDLWrapper&) = delete;
  SDLWrapper& operator=(const SDLWrapper&) = delete;
};

#endif
