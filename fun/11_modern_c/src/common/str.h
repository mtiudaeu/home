#ifndef COMMON_STR_H
#define COMMON_STR_H

#include <stddef.h>
#include <stdbool.h>

typedef void (*allocator_cb) (size_t size); 

typedef struct str {
 char* data;
 size_t size;
} str;

typedef struct str_buf {
 char* data;
 size_t size;
 size_t capacity;
 allocator_cb allocator;
} str_buf;

str_buf str_buf_make(size_t size, allocator_cb allocator);
void str_buf_append(str_buf* str_buf_ptr, str str);
void str_buf_remove(str_buf* str_buf_ptr, size_t begin, size_t end);
str str_buf_str(str_buf str_buf);

bool str_valid(str str);
bool str_match(str a, str b);
bool str_contains(str haystack, str needle);
str str_sub(str src, size_t begin, size_t end);
str str_find_first(str haystack, str needle);
str str_find_last(str haystack, str needle);
str str_remove_prefix(str src, str prefix);
str str_remove_suffix(str src, str suffix);



#endif //COMMON_STR_H
