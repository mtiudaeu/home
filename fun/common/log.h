#include <stdio.h>

#define LOG_ERROR(...)                                     \
  fprintf(stderr, "error : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__);                            \
  fprintf(stderr, "\n");


//MDTMP
