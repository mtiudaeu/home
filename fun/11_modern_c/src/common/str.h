#ifndef COMMON_STR_H
#define COMMON_STR_H

#include <stddef.h>
#include <stdbool.h>

#include "common/allocator_cbs.h"

typedef struct str {
 const char* data;
 size_t size;
} str;

typedef struct str_buf {
 allocator_cbs allocator_cbs;
 char* data;
 size_t size;
 size_t capacity;
} str_buf;

str_buf str_buf_create(size_t size, allocator_cbs allocator_cbs);
str_buf str_buf_destroy(str_buf str_buf);
void str_buf_append(str_buf* str_buf_ptr, str str);
void str_buf_remove(str_buf* str_buf_ptr, size_t begin, size_t end_exclusive);
str str_buf_str(str_buf str_buf);

bool str_valid(str str);
bool str_match(str a, str b);
bool str_contains(str haystack, str needle);
str str_sub(str src, size_t begin, size_t end);
str str_find_first(str haystack, str needle);
str str_find_last(str haystack, str needle);
str str_remove_prefix(str src, str prefix);
str str_remove_suffix(str src, str suffix);
str str_cstr(const char* cstr);



#endif //COMMON_STR_H
