#ifndef COMMON_STR_H
#define COMMON_STR_H

#include <stddef.h>
#include <stdbool.h>

#include "common/allocator_cbs.h"

struct str {
 const char* data;
 size_t size;
};

struct str_buf {
 struct allocator_cbs allocator_cbs;
 char* data;
 size_t size;
 size_t capacity;
};

struct str_buf str_buf_create(size_t size, struct allocator_cbs allocator_cbs);
struct str_buf str_buf_destroy(struct str_buf str_buf);
void str_buf_append(struct str_buf* str_buf_ptr, struct str str);
void str_buf_remove(struct str_buf* str_buf_ptr, size_t begin, size_t end);
struct str str_buf_str(struct str_buf str_buf);

bool str_valid(struct str str);
bool str_match(struct str a, struct str b);
bool str_contains(struct str haystack, struct str needle);
struct str str_sub(struct str src, size_t begin, size_t end);
struct str str_find_first(struct str haystack, struct str needle);
struct str str_find_last(struct str haystack, struct str needle);
struct str str_remove_prefix(struct str src, struct str prefix);
struct str str_remove_suffix(struct str src, struct str suffix);
struct str cstr(const char* cstr);



#endif //COMMON_STR_H
