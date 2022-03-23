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

#define dyn_buf_add(dyn_buf, element)                                    \
do {                                                                      \
 _dyn_buf_ensure_capacity_for_add(&dyn_buf.dyn_buf_info, &dyn_buf.data);         \
 dyn_buf.data[dyn_buf.dyn_buf_info.size] = element;                    \
 dyn_buf.dyn_buf_info.size++;                                           \
}                                                                         \
while(0)

void _dyn_buf_ensure_capacity_for_add(struct dyn_buf_info* dyn_buf_info, void* data);

#endif
