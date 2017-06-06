#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_ERROR(...)                                     \
  fprintf(stderr, "error : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__);                            \
  fprintf(stderr, "\n");

#ifdef LOG_DEBUG_ENABLED
#define LOG_DEBUG(...)                                     \
  fprintf(stdout, "debug : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stdout, __VA_ARGS__);                            \
  fprintf(stdout, "\n");
#else
#define LOG_DEBUG(...)
#endif

#endif  // LOG_H
