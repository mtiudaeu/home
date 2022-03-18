#include "common/str.h"
#include "common/macros.h"
#include <string.h>

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
void str_buf_remove(str_buf* str_buf_ptr, size_t begin, size_t end)
{
}

//--------------------
str str_buf_str(str_buf str_buf)
{
 str str;
 return str;
}

//--------------------
bool str_valid(str str)
{
 return false;
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
 str str;
 return str;
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



