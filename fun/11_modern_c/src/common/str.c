#include "common/str.h"
#include "common/macros.h"
#include "common/log.h"

#include <string.h>
#include <assert.h>

static const struct str invalid_str = {
 .data = 0x0,
 .size=0
};

//--------------------
struct str_buf str_buf_create(size_t size, struct allocator_cbs allocator_cbs)
{
 const size_t size_of_one = sizeof(char);
 char* data = allocator_cbs.malloc(size*size_of_one);

 struct str_buf str_buf = dyn_buf_create(int, size, allocator_cbs);
/*
 struct str_buf str_buf = {
  .dyn_buf_info = {
   .allocator_cbs=allocator_cbs,
   .size=0,
   .capacity=size,
   .size_of_one=size_of_one
  },
  .data=data
 };
*/
 return str_buf;
}

//--------------------
void str_buf_destroy(struct str_buf* str_buf_ptr)
{
 str_buf_ptr->dyn_buf_info.allocator_cbs.free(str_buf_ptr->data);
 str_buf_ptr->data = 0x0;
}

//--------------------
void str_buf_append(struct str_buf* str_buf_ptr, struct str str)
{
 if(!str_valid(str)) {
  return;
 }
 const size_t new_size = str_buf_ptr->dyn_buf_info.size + str.size;
 if(new_size > str_buf_ptr->dyn_buf_info.capacity)
 {
  size_t new_capacity = MAX((2 * str_buf_ptr->dyn_buf_info.capacity), new_size);
  str_buf_ptr->data = str_buf_ptr->dyn_buf_info.allocator_cbs.realloc(str_buf_ptr->data, new_capacity * str_buf_ptr->dyn_buf_info.size_of_one);

  str_buf_ptr->dyn_buf_info.capacity = new_capacity;
 }

 size_t old_size = str_buf_ptr->dyn_buf_info.size;
 char* begin = str_buf_ptr->data + old_size;
 memcpy(begin, str.data, str.size);
 str_buf_ptr->dyn_buf_info.size = new_size;
}

//--------------------
// overwrite the deleted part with the rest of the buffer
void str_buf_remove(struct str_buf* str_buf_ptr, size_t begin, size_t end)
{
 size_t prev_str_buf_size = str_buf_ptr->dyn_buf_info.size;
 size_t valid_end = MIN(end, prev_str_buf_size);

 if(valid_end <= begin) {
  return;
 }
 size_t valid_begin = begin;

 size_t remove_size = valid_end - valid_begin;
 size_t copy_size = valid_end - prev_str_buf_size;
 size_t new_str_buf_size = prev_str_buf_size - remove_size;

 char* dest_begin = str_buf_ptr->data + valid_begin;
 char* src_begin = dest_begin + remove_size;
 memcpy(dest_begin, src_begin, copy_size * str_buf_ptr->dyn_buf_info.size_of_one);

 str_buf_ptr->dyn_buf_info.size = new_str_buf_size;
}

//--------------------
struct str str_buf_str(struct str_buf str_buf)
{
 struct str str = 
 {
  .data = str_buf.data,
  .size = str_buf.dyn_buf_info.size,
 };

 return str;
}

//--------------------
bool str_valid(struct str str)
{
 return str.data != 0x0;
}

//--------------------
bool str_match(struct str a, struct str b)
{
 if(!str_valid(a) || !str_valid(b)) {
  return false;
 }
 if(a.size != b.size) {
  return false;
 }

 const char* a_itr = a.data;
 const char* a_end = a_itr + a.size; 
 const char* b_itr = b.data;
 for(; a_itr != a_end; a_itr++, b_itr++ )
 {
  if(*a_itr != *b_itr) {
   return false;
  }
 }

 return true;
}

//--------------------
bool str_contains(struct str haystack, struct str needle)
{
 struct str ret = str_find_first(haystack, needle);
 return str_valid(ret);
}

//--------------------
struct str str_sub(struct str src, size_t begin, size_t end)
{
 if(!str_valid(src)) {
  return invalid_str; 
 }
 if(end > src.size || begin >= end) {
  return invalid_str;
 }

 const char* begin_str = src.data + begin;
 size_t new_size = end - begin;
 struct str new_str = {
  .data = begin_str,
  .size = new_size
 }; 
 return new_str;
}

//--------------------
struct str str_find_first(struct str haystack, struct str needle)
{
 if(!str_valid(haystack) || !str_valid(needle)) {
  return invalid_str;
 }

 size_t haystack_size = haystack.size;
 size_t needle_size = needle.size; 

 size_t begin = 0;
 size_t end = begin + needle_size;
 for(; end <= haystack_size; begin++, end = begin + needle_size)
 {
  struct str haystack_part = str_sub(haystack, begin, end);
  if(str_match(haystack_part, needle))
  {
   return haystack_part;
  }
 }
 return invalid_str;
}

//--------------------
struct str str_find_last(struct str haystack, struct str needle)
{
 if(!str_valid(haystack) || !str_valid(needle)) {
  return invalid_str;
 }
 
 const size_t haystack_size = haystack.size;
 const size_t needle_size = needle.size;
 if(needle_size > haystack_size) {
  return invalid_str;
 }

 size_t end = haystack_size;
 size_t begin = haystack_size - needle_size;
 for(;; end--, begin = haystack_size - needle_size) {
  
  struct str haystack_part = str_sub(haystack, begin, end);
  if(str_match(haystack, needle)) {
   return haystack_part;
  }
  if(begin == 0) {
   break;
  }
 }

 return invalid_str;
}

//--------------------
struct str str_remove_prefix(struct str src, struct str prefix)
{
 LOG_ERROR("unimplemented");
 assert(0);
 struct str str;
 return str;
}

//--------------------
struct str str_remove_suffix(struct str src, struct str suffix)
{
 LOG_ERROR("unimplemented");
 assert(0);
 struct str str;
 return str;
}

//--------------------
struct str cstr(const char* cstr)
{
 size_t size = strlen(cstr);
 struct str str = {
  .data = cstr,
  .size = size
 };
 return str;
}



