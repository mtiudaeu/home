#include <app.h>

#include <macros.h>

#include <iostream>

struct App::Imp {
  // MDTMP
};

App::App() : m_imp(new App::Imp()) {
  // MDTMP
  std::cout << "App:App\n";
}

App::~App() {
  delete m_imp;
  m_imp = nullptr;
}

int App::run() noexcept {
  try {
    // MDTMP
    THROW_ERR("LABLABLABLA");
  } catch (const std::exception& e) {
    std::cout << e.what() << "\n";
  }

  return 0;
}
