#include "test/test_common_dyn_buf.h"

#include "common/dyn_buf.h"

#include <assert.h>

//--------------------------------------------------
void test_common_dyn_buf(struct allocator_cbs allocator)
{
 struct generic_dyn_buf(int) dyn_buf = dyn_buf_create(int, 4, allocator);

 int tmp = 1;
 dyn_buf_add(dyn_buf, tmp);

 dyn_buf_add(dyn_buf, 2);
 dyn_buf_add(dyn_buf, 2);
 dyn_buf_add(dyn_buf, 2);
 dyn_buf_add(dyn_buf, 2);
 dyn_buf_add(dyn_buf, 2);

 const int const* ref_begin = dyn_buf_begin(dyn_buf);
 const int* begin = dyn_buf_begin(dyn_buf);
 const int const* end = dyn_buf_end(dyn_buf);
 for(;begin < end; begin++) {
  if(begin == ref_begin) {
   assert(*begin == 1);
  } else {
   assert(*begin == 2);
  }
 }
  
}
