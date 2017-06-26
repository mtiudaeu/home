#ifndef CORE_DATA_DATA_MANAGER_H
#define CORE_DATA_DATA_MANAGER_H

#include <stdlib.h>

struct imp_s;
class data_manager_s {
  imp_s* imp_;

  public:
  data_manager_s();
  ~data_manager_s();
  void* get_data(size_t id);
};

#endif
