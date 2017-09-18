#ifndef APP_H
#define APP_H

class App {
 struct Imp;
 Imp* m_imp;
 public:
  App();
  ~App();

  int run() noexcept;

  App(const App&) = delete;
  App& operator=(const App&) = delete;
};

#endif
