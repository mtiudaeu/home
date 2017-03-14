#include "module.h"

#include <unistd.h>
#include <stdio.h>

int main() {
  module::library library;
  module::load(library, "hello.so");
  for (;;) {
    printf("hello!\n");
    sleep(1);
  }
  return 0;
}
