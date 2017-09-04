#include "app.h"

#include "gl/context.h"

namespace {

Status init() {
  Status status;
  status = gl_context_init();
  return status;
}
}

int main() {
  Status status = init();
  if (!status) {
    LOG_ERROR(status);
    return 1;
  }

  while (1) {
    const Status status = gl_context_swap_buffer();
    if (!status) {
      LOG_ERROR(status);
    }
  }

  return 0;
}
