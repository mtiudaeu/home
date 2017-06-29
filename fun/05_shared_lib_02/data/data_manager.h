#ifndef CORE_DATA_DATA_MANAGER_H
#define CORE_DATA_DATA_MANAGER_H

#include "data/data_type.h"

#include <string>

#include <stdlib.h>

#define DM_GET_DATA(data_manager, type, path) \
  static_cast<type*>((data_manager).get_data(path, type::m_data_type));

struct imp_s;
class data_manager_s {
  imp_s* imp_;

  public:
  data_manager_s();
  ~data_manager_s();
  void* get_data(const std::string path, data_type_e type_id);
};

#endif
