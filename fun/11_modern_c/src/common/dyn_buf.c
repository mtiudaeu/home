#include "common/dyn_buf.h"

void _dyn_buf_ensure_capacity_for_add(struct dyn_buf_info* dyn_buf_info, void** data)
{
 const size_t new_size = dyn_buf_info->size + 1;
 if(new_size > dyn_buf_info->capacity)
 {
  size_t new_capacity = 2 * dyn_buf_info->capacity;
  *data = dyn_buf_info->allocator_cbs.realloc(*data, new_capacity * dyn_buf_info->size_of_one);

  dyn_buf_info->capacity = new_capacity;
 }
}
