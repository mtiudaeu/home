#ifndef COMMON_DYN_ARRAY_H
#define COMMON_DYN_ARRAY_H

#include "common/allocator_cbs.h"
/*
typedef struct dyn_array_info
{
  size_t size;
  size_t capacity;
  size_t size_of_one;
  allocator_cbs allocator;
} dyn_array_info;

#define dyn_array_create(capacity, size_of_one, allocator, type) \
 struct {\
  type* data;\
  dyn_array_info info;\  
 }

#define dyn_array_begin(dyn_array) \
dyn_array.data

#define dyn_array_end(dyn_array) \
dyn_array.date + dyn_array.header.size



 */

dyn_array* _dyn_array_create(size_t capacity, size_t size_of_one, allocator_cbs allocator);
dyn_array dyn_array_destroy(dyn_array dyn_array);

void dyn_array_push_back(dyn_array dyn_array, void* elem);
void dyn_array_pop_back(dyn_array dyn_array);
void dyn_array_clear(dyn_array dyn_array);

#endif
