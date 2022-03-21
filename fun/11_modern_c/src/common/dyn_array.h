#ifndef COMMON_DYN_ARRAY_H
#define COMMON_DYN_ARRAY_H

#include "common/allocator_cbs.h"

typedef struct dyn_array
{
  void* data;
  size_t size;
  size_t capacity;
  size_t size_of_one;
  allocator_cbs allocator;
} dyn_array;

dyn_array* dyn_array_create(size_t capacity, size_t size_of_one, allocator_cbs allocator);
dyn_array dyn_array_destroy(dyn_array dyn_array);

void dyn_array_push_back(dyn_array dyn_array, void* elem);
void dyn_array_pop_back(dyn_array dyn_array);
void dyn_array_clear(dyn_array dyn_array);

#endif
