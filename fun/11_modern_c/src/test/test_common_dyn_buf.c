#include "test/test_common_dyn_buf.h"

#include "common/dyn_buf.h"

//--------------------------------------------------
void test_common_dyn_buf(struct allocator_cbs allocator)
{
//mdtmp

 struct generic_dyn_buf(int) dyn_buf = {0};

 //struct generic_dyn_buf(int) dyn_buf = dyn_buf_create();???
 dyn_buf_add(dyn_buf, 1);// segmentation fault without create

 
  
}
