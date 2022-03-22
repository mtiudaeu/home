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
  dyn_array_info info;\ 
  type* data;\ 
 }

#define dyn_array_begin(dyn_array) \
dyn_array.data

#define dyn_array_end(dyn_array) \
dyn_array.date + dyn_array.header.size

#define dyn_array_add(dyn_array, elem) \
if(dyn_array.capacity <= dyn_array.size) {\
 dyn_array.capacity * = 2;
 dyn_array.data = realloc(dyn_array.data, dyn_array.capacity * dyn_array.size_of_one);
}\




 */

dyn_array* _dyn_array_create(size_t capacity, size_t size_of_one, allocator_cbs allocator);
dyn_array dyn_array_destroy(dyn_array dyn_array);

void dyn_array_push_back(dyn_array dyn_array, void* elem);
void dyn_array_pop_back(dyn_array dyn_array);
void dyn_array_clear(dyn_array dyn_array);

#endif
