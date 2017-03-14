#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_ERROR(...)                                     \
  fprintf(stderr, "error : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__);                            \
  fprintf(stderr, "\n");

#define LOG_INFO(...)                                     \
  fprintf(stdout, "info : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stdout, __VA_ARGS__);                            \
  fprintf(stdout, "\n");

#endif // LOG_H
