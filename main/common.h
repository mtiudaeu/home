#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <iostream>

struct nocopy {
  nocopy() = default;
  nocopy(const nocopy&) = delete;
  nocopy& operator = (const nocopy&) = delete;
};

#define LOG_ERROR(...)                                     \
  fprintf(stderr, "error : %s:%d : ", __FILE__, __LINE__); \
  fprintf(stderr, __VA_ARGS__);                            \
  fprintf(stderr, "\n");

#define LOG(...)                                     \
  fprintf(stdout, "%s:%d : ", __FILE__, __LINE__); \
  fprintf(stdout, __VA_ARGS__);                            \
  fprintf(stdout, "\n");

#endif
