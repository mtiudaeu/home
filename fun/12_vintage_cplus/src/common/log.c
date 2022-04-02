#include "common/log.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

static struct allocator_cbs allocator =
{
 .malloc=&malloc,
 .realloc=&realloc,
 .free=&free
};

static void _print(int fd, const char* fmt, va_list* vl);

//--------------------------------------------------
static void _print_str_fd(int fd, struct str str) {
  write(fd, str.data, str.size);
}

//--------------------------------------------------
void print(const char* fmt, ...)
{
 va_list vl;

 va_start(vl, fmt);
 _print(1, fmt, &vl);

 va_end(vl);
 _print_str_fd(1, cstr("\n"));
}

//--------------------------------------------------
void print_fd(int fd, const char* fmt, ...)
{
 va_list vl;

 va_start(vl, fmt);
 _print(fd, fmt, &vl);

 va_end(vl);
}

//--------------------------------------------------
static void _print(int fd, const char* fmt, va_list* vl)
{
 char buffer [33];
 struct str fmt_str_itr = cstr(fmt);
 struct str_buf str_buf = str_buf_create(10, allocator);


 struct str found = str_find_first(fmt_str_itr, cstr("%")); 

 while(str_valid(found)) {
  size_t found_offset = found.data - fmt_str_itr.data;

  const struct str prefix_to_append = str_sub(fmt_str_itr, 0, found_offset);
  str_buf_append(&str_buf, prefix_to_append);

  fmt_str_itr = str_sub(fmt_str_itr, found_offset, fmt_str_itr.size);

  if(fmt_str_itr.size >=2) {
    switch(fmt_str_itr.data[1]) {
     case 's' : {
       const char* buf = va_arg(*vl, char*);
       str_buf_append(&str_buf, cstr(buf));
      break;
     }
     case 'd' : {
       snprintf(buffer, sizeof(buffer), "%d", va_arg(*vl, int));
       str_buf_append(&str_buf, cstr(buffer));
      break;
     }
    }
  }

  fmt_str_itr = str_sub(fmt_str_itr, 2, fmt_str_itr.size);
  found = str_find_first(fmt_str_itr, cstr("%")); 
 }

 str_buf_append(&str_buf, fmt_str_itr);
 
 _print_str_fd(fd, str_buf_str(str_buf));
 
 str_buf_destroy(&str_buf);
}
