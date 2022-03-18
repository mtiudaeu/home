#include "common/log.h"

#include <unistd.h>

void print_str(str str) {
  write(1, str.data, str.size);
  write(1, "\n", 1);
}
