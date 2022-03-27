#include "common/dyn_buf.h"
#include "common/macros.h"

#include <stdlib.h>
#include <string.h>

//--------------------------------------------------
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

//--------------------------------------------------
void _dyn_buf_destroy(struct dyn_buf_info* dyn_buf_info, void** data)
{
 dyn_buf_info->allocator_cbs.free(*data);
 *data = 0x0;
 dyn_buf_info->size = 0;
 dyn_buf_info->capacity = 0;
}

//--------------------------------------------------
int _dyn_buf_comparator_int(void* lhs, void* rhs)
{
 int* i_lhs = (int*) lhs;
 int* i_rhs = (int*) rhs;

 if(*i_lhs == *i_rhs) {
  return 0;
 } else if (*i_lhs < *i_rhs) {
  return -1;
 }
 return 1;
}

//--------------------------------------------------
void _max_heap(struct dyn_buf_info dyn_buf_info, void* data, int (*comparator)(void* lhs, void* rhs))
{
 const size_t size_of_one = dyn_buf_info.size_of_one;
 const size_t size = dyn_buf_info.size; 
 const struct allocator_cbs allocator_cbs = dyn_buf_info.allocator_cbs;

 void* tmp = allocator_cbs.malloc(size_of_one);
 SCOPE(allocator_cbs.free(tmp))
 {
  size_t i = 0;
  for(;i < size; i++) {
   size_t i_child = i;
   while(i_child != 0) {
    size_t i_parent = (i_child-1)/2;

    void* child = data + (size_of_one*i_child);
    void* parent = data + (size_of_one*i_parent);
    if(comparator(parent, child) >= 0) {
     // child is smaller. We are done.
     break;
    }
    
    memcpy(tmp, parent, size_of_one);
    memcpy(parent, child, size_of_one);
    memcpy(child, tmp, size_of_one);

    i_child = i_parent;
   }
  }
 }
 
}

void _heapify(struct dyn_buf_info dyn_buf_info, void* data, int (*comparator)(void* lhs, void* rhs))
{
 const size_t size = dyn_buf_info.size;
 const size_t size_of_one = dyn_buf_info.size_of_one;
 const struct allocator_cbs allocator_cbs = dyn_buf_info.allocator_cbs;
 
 void* tmp = allocator_cbs.malloc(size_of_one);
 SCOPE(allocator_cbs.free(tmp))
 {
  size_t i_node = 0; 
  while(1)
  {
   size_t i_child1 = i_node*2 + 1;
   size_t i_child2 = i_node*2 + 2;

   if(i_child1 >= size) {
    break;
   }
   size_t i_max_child = i_child1;
   if(i_child2 < size) {
    void* child1 = data + size_of_one*i_child1;
    void* child2 = data + size_of_one*i_child2;
    if(comparator(child1, child2) < 0) {
     i_max_child = i_child2;
    }
   }
   
   void* node = data + size_of_one*i_node;
   void* max_child = data + size_of_one*i_max_child;
   if(comparator(node, max_child) < 0) {
    memcpy(tmp, node, size_of_one);
    memcpy(node, max_child, size_of_one);
    memcpy(max_child, tmp, size_of_one);
    i_node = i_max_child;
    continue;
   }

   break;
  }
 }
}
//--------------------------------------------------
void _dyn_buf_sort(struct dyn_buf_info dyn_buf_info, void* data, int (*comparator)(void* lhs, void* rhs))
{
 const size_t size_of_one = dyn_buf_info.size_of_one; 
 const size_t size = dyn_buf_info.size;
 const struct allocator_cbs allocator_cbs = dyn_buf_info.allocator_cbs;

 _max_heap(dyn_buf_info, data, comparator);

 void* tmp = allocator_cbs.malloc(size_of_one);
 SCOPE(allocator_cbs.free(tmp))
 {
  for(int i = ((int)size)-1; i>0; i--) {
   void* first = data;
   void* last = data + i*size_of_one; 
   memcpy(tmp, first, size_of_one);
   memcpy(first, last, size_of_one);
   memcpy(last, tmp, size_of_one);
 
   dyn_buf_info.size--;
   _heapify(dyn_buf_info, data, comparator);
  }
 }
 
}














