#ifndef CORE_DATA_MANAGER_H
#define CORE_DATA_MANAGER_H

#include <memory>

// TODO Design a proper data acces API. Most be flexible, control access + type safe ish
struct imp_s;
class data_manager_s {
  std::unique_ptr<imp_s> imp_;

  public:
  data_manager_s();
  ~data_manager_s();
  void* get_data(size_t id);

  // FIXME Hack
  enum {
    ID_MODULES = 0,
    ID_DATA
  };
};

#endif
