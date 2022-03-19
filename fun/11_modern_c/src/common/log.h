#ifndef COMMON_LOG_H
#define COMMON_LOG_H

#include "common/str.h"

#include <stdio.h>

#define LOG_ERROR(...)                         \
  print_fd(2, "[error] ");                     \
  print_fd(2, __VA_ARGS__);                    \
  print_fd(2, " (%s:%d)", __FILE__, __LINE__); \
  print_fd(2, "\n");


#ifdef DEBUG_TRACE
#define LOG_TRACE(...)                         \
  print_fd(2, "[trace] ");                     \
  print_fd(2, __VA_ARGS__);                    \
  print_fd(2, " (%s:%d)", __FILE__, __LINE__); \
  print_fd(2, "\n");
#else
#define LOG_TRACE(...) do { } while(0)
#endif

void print(const char* fmt, ...);
void print_fd(int fd, const char* fmt, ...);

#endif // COMMON_LOG_H
