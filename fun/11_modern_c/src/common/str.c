#include "common/str.h"
#include "common/macros.h"
#include <string.h>

static const str invalid_str = {
 .data = 0x0,
 .size=0
};

//--------------------
str_buf str_buf_create(size_t size, allocator_cbs allocator_cbs)
{
 char* data = allocator_cbs.malloc(size*sizeof(char));

 str_buf str_buf = {
  .allocator_cbs=allocator_cbs,
  .data=data,
  .size=0,
  .capacity=size
 };
 return str_buf;
}

//--------------------
str_buf str_buf_destroy(str_buf str_buf)
{
 str_buf.allocator_cbs.free(str_buf.data);
 str_buf.data = 0x0;
 return str_buf;
}

//--------------------
void str_buf_append(str_buf* str_buf_ptr, str str)
{
 const size_t new_size = str_buf_ptr->size + str.size;
 if(new_size > str_buf_ptr->capacity)
 {
  size_t new_capacity = MAX((2 * str_buf_ptr->capacity), new_size);
  str_buf_ptr->data = str_buf_ptr->allocator_cbs.realloc(str_buf_ptr->data, new_capacity * sizeof(char));

  str_buf_ptr->capacity = new_capacity;
 }

 size_t old_size = str_buf_ptr->size;
 char* begin = str_buf_ptr->data + old_size;
 memcpy(begin, str.data, str.size);
 str_buf_ptr->size = new_size;
}

//--------------------
// overwrite the deleted part with the rest of the buffer
void str_buf_remove(str_buf* str_buf_ptr, size_t begin, size_t end)
{
 size_t prev_str_buf_size = str_buf_ptr->size;
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
 memcpy(dest_begin, src_begin, copy_size * sizeof(char));

 str_buf_ptr->size = new_str_buf_size;
}

//--------------------
str str_buf_str(str_buf str_buf)
{
 str str = 
 {
  .data = str_buf.data,
  .size = str_buf.size,
 };

 return str;
}

//--------------------
bool str_valid(str str)
{
 return str.data != 0x0;
}

//--------------------
bool str_match(str a, str b)
{
 return false;
}

//--------------------
bool str_contains(str haystack, str needle)
{
 return false;
}

//--------------------
str str_sub(str src, size_t begin, size_t end)
{
 if(!str_valid(src)) {
  return invalid_str; 
 }
 if(end > src.size || end >= begin) {
  return invalid_str;
 }

 const char* begin_str = src.data + begin;
 size_t new_size = end - begin;
 str new_str = {
  .data = begin_str,
  .size = new_size
 }; 
 return new_str;
}

//--------------------
str str_find_first(str haystack, str needle)
{
 str str;
 return str;
}

//--------------------
str str_find_last(str haystack, str needle)
{
 str str;
 return str;
}

//--------------------
str str_remove_prefix(str src, str prefix)
{
 str str;
 return str;
}

//--------------------
str str_remove_suffix(str src, str suffix)
{
 str str;
 return str;
}

//--------------------
str cstr(const char* cstr)
{
 size_t size = strlen(cstr);
 str str = {
  .data = cstr,
  .size = size
 };
 return str;
}



