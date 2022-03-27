#ifndef COMMON_DYN_BUF_H
#define COMMON_DYN_BUF_H

#include "common/allocator_cbs.h"

struct dyn_buf_info {
 struct allocator_cbs allocator_cbs;
 size_t size;
 size_t capacity;
 size_t size_of_one;
};

#define generic_dyn_buf(type)             \
{                                 \
 struct dyn_buf_info dyn_buf_info;\
 type* data;                      \
}

//--------------------------------------------------
#define dyn_buf_create(type, param_capacity, param_allocator_cbs) \
{                                                                  \
 .dyn_buf_info = {                                                 \
  .allocator_cbs=param_allocator_cbs,                            \
  .size = 0,                                                       \
  .capacity = param_capacity,                                      \
  .size_of_one= sizeof(type)                                       \
 },                                                                \
 .data=param_allocator_cbs.malloc(sizeof(type)*param_capacity)    \
}

#define dyn_buf_destroy(dyn_buf)                          \
_dyn_buf_destroy(&((dyn_buf)->dyn_buf_info), (void**)&((dyn_buf)->data))

void _dyn_buf_destroy(struct dyn_buf_info* dyn_buf_info, void** data);

//--------------------------------------------------
#define dyn_buf_begin(dyn_buf) \
dyn_buf.data

#define dyn_buf_end(dyn_buf) \
dyn_buf.data + dyn_buf.dyn_buf_info.size

//--------------------------------------------------
#define dyn_buf_add(dyn_buf, element)                                    \
do {                                                                      \
 _dyn_buf_ensure_capacity_for_add(&dyn_buf.dyn_buf_info, (void**)&dyn_buf.data);         \
 dyn_buf.data[dyn_buf.dyn_buf_info.size] = element;                    \
 dyn_buf.dyn_buf_info.size++;                                           \
}                                                                         \
while(0)

void _dyn_buf_ensure_capacity_for_add(struct dyn_buf_info* dyn_buf_info, void** data);

//--------------------------------------------------
int _dyn_buf_comparator_int(void* lhs, void* rhs);

#define generic_dyn_buf_sort(dyn_buf) \
 _generic_dyn_buf_sort(dyn_buf.dyn_buf_info, dyn_buf.data, *dyn_buf.data)

#define _generic_dyn_buf_sort(dyn_buf_info, data, typed_var) \
 _dyn_buf_sort(dyn_buf_info, (void*) data,                   \
 _Generic(typed_var, int: &_dyn_buf_comparator_int))

void _dyn_buf_sort(struct dyn_buf_info dyn_buf_info, void* data, int (*comparator)(void* lhs, void* rhs));

//--------------------------------------------------
/*
void dyn_buf_pop_back(dyn_buf dyn_buf);
void dyn_buf_clear(dyn_buf dyn_buf);

*/

#endif
