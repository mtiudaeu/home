#ifndef COMMON_DYN_BUF_H
#define COMMON_DYN_BUF_H

typedef struct dyn_buf_info {
 size_t size;
 size_t capacity;
 size_t size_of_one;
} dyn_buf_info;

#define dyn_buf(type)      \
{                          \
 dyn_buf_info dyn_buf_info;\
 type* data;               \
}

/*
Usage :
struct char_buf dyn_buf(char);
struct dyn_buf(int);
*/
#endif
