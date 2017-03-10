#include "module.h"

#include <unistd.h>
#include <stdio.h>

int main() {
  for (;;) {
    printf("hello!\n");
    sleep(1);
  }
  return 0;
}
