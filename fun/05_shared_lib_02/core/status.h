#ifndef STATUS_H
#define STATUS_H

#include <sys/types.h>

struct status_s {
  bool error = false;
  size_t info_code = 0;
};

#endif
