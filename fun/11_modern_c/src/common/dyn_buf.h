#ifndef COMMON_DYN_BUF_H
#define COMMON_DYN_BUF_H

typedef struct dyn_buf_info {
 size_t size;
 size_t capacity;
 size_t size_of_one;
} dyn_buf_info;

#endif
