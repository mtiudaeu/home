#ifndef COMMON_DYN_BUF_H
#define COMMON_DYN_BUF_H

struct dyn_buf_info {
 struct allocator_cbs allocator_cbs;
 size_t size;
 size_t capacity;
 size_t size_of_one;
};

#define generic_dyn_buf(type)             \
{                                 \
 struct dyn_buf_info dyn_buf_info;\
 type* data;                      \
}

/*
Usage :
struct char_buf generic_dyn_buf(char);
struct generic_dyn_buf(int);
*/
#endif
