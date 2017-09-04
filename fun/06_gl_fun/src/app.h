#ifndef APP_H
#define APP_H

#include "ehLogger.h"

#include "status.h"

#include <cstdlib>
#include <iostream>

struct App {
  struct Module : public eh::Logger::Module {
    enum Level { ERROR = 0, INFO, DEBUG };

    Level m_level = Level::DEBUG;

    Module() {}
    Module(Module::Level level) : m_level(level) {}

    virtual std::string toString() const override {
      switch (m_level) {
      case Level::ERROR:
        return "ERROR:";
      case Level::INFO:
        return "INFO:";
      case Level::DEBUG:
        return "DEBUG:";
      }
      return "";
    }
    virtual void overrideStream(std::ostream *&os) const override {
      os = &std::cout;
    }
    virtual bool isActive() const override {
      return m_level <= App::get().m_logModule.m_level;
    }
  };

  Module m_logModule;
  eh::Msg::Separator m_msgSeparator;

  static const App &get() {
    static App app;
    return app;
  }

  template <typename... Ts>
  static Status buildStatus(const eh::Msg::Separator &separator, Status::Id id,
                            const Ts &... args) {

    const std::string msg = eh::Msg::build(separator, args...);
    return Status(id, msg);
  }

private:
  App() {
    if (const char *levelEnv = std::getenv("EH_LOGGER_LEVEL")) {
      const std::string levelStr = levelEnv;
      try {
        const int level = std::stoi(levelStr);
        if (level >= Module::Level::ERROR && level <= Module::Level::DEBUG) {
          m_logModule.m_level = static_cast<Module::Level>(level);
        }
      } catch (...) {
      }
    }
  }

  App(const App &) = delete;
  App &operator=(const App &) = delete;
};

#define LOG_ERROR(...)                                                         \
  (eh::Logger::log(App::Module(App::Module::Level::ERROR),                     \
                   App::get().m_msgSeparator, __VA_ARGS__,                     \
                   EH_BUILD_FILE_INFO));

#define LOG_INFO(...)                                                          \
  (eh::Logger::log(App::Module(App::Module::Level::INFO),                      \
                   App::get().m_msgSeparator, __VA_ARGS__));
#define LOG_DEBUG(...)                                                         \
  (eh::Logger::log(App::Module(App::Module::Level::DEBUG),                     \
                   App::get().m_msgSeparator, __VA_ARGS__,                     \
                   EH_BUILD_FILE_INFO));

#define BUILD_ERROR(...)                                                       \
  (App::buildStatus(App::get().m_msgSeparator, Status::FAILURE, __VA_ARGS__,   \
                    EH_BUILD_FILE_INFO))

#define BUILD_STATUS(...)                                                      \
  (App::buildStatus(App::get().m_msgSeparator, __VA_ARGS__, EH_BUILD_FILE_INFO))

#endif
