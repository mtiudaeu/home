#ifndef DATA_DATA_TYPE_H
#define DATA_DATA_TYPE_H

#define DT_ID_HEADER(type) \
  static const data_type_e m_data_type = type;

#define DT_GET_TYPE(type) \
  type.m_data_type

enum data_type_e {
  DT_MODULES = 0,
  DT_GAME
};

#endif

