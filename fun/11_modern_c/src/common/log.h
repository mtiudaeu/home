#ifndef COMMON_LOG_H
#define COMMON_LOG_H

#include "common/str.h"

#include <stdio.h>

#define LOG_ERROR(...)                                     \
  fprintf(stderr, "error : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__);                            \
  fprintf(stderr, "\n");

#ifdef DEBUG_TRACE
#define LOG_TRACE(...)                                     \
  fprintf(stderr, "trace : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__);                            \
  fprintf(stderr, "\n");
#else
#define LOG_TRACE(...) do { } while(0)
#endif

//#define PRINT(...) 
void print_str(str str);

#endif // COMMON_LOG_H
