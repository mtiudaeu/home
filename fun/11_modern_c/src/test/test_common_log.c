#include "test/test_common_log.h"

#include "common/str.h"
#include "common/log.h"

#include <stdlib.h>
#include <stdarg.h>

static allocator_cbs allocator =
{
 .malloc=&malloc,
 .realloc=&realloc,
 .free=&free
};

void print_test(const char* fmt, ...) {
 va_list vl;
 va_start(vl, fmt);

 char buffer [33];
 str fmt_str_itr = cstr(fmt);
 str_buf str_buf = str_buf_create(10, allocator);


 str found = str_find_first(fmt_str_itr, cstr("%")); 

 while(str_valid(found)) {
  size_t found_offset = found.data - fmt_str_itr.data;

  const str prefix_to_append = str_sub(fmt_str_itr, 0, found_offset);
  str_buf_append(&str_buf, prefix_to_append);

  fmt_str_itr = str_sub(fmt_str_itr, found_offset, fmt_str_itr.size);

  if(fmt_str_itr.size >=2) {
    switch(fmt_str_itr.data[1]) {
     case 's' : {
       const char* buf = va_arg(vl, char*);
       str_buf_append(&str_buf, cstr(buf));
      break;
     }
     case 'd' : {
       snprintf(buffer, sizeof(buffer), "%d", va_arg(vl, int));
       str_buf_append(&str_buf, cstr(buffer));
      break;
     }
    }
  }

  fmt_str_itr = str_sub(fmt_str_itr, 2, fmt_str_itr.size);
  found = str_find_first(fmt_str_itr, cstr("%")); 
 }
 va_end(vl);

 str_buf_append(&str_buf, fmt_str_itr);
 
 print_str(str_buf_str(str_buf));
 
 str_buf = str_buf_destroy(str_buf);
}

//--------------------
void test_common_log_run(allocator_cbs allocator)
{
  
 str_buf str_buf = str_buf_create(10, allocator);
 str_buf_append(&str_buf, cstr("Hey"));
 
 print_str(str_buf_str(str_buf));

 str_buf = str_buf_destroy(str_buf);
 
 print_test("%s:%s:%s", "test", "hey", "sup");
 print_test("hey : %d",1131);
}
