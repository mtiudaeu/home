#include "test/test_common_dyn_buf.h"

#include "common/dyn_buf.h"
#include "common/macros.h"
#include "common/log.h"

#include <assert.h>

//--------------------------------------------------
void test_common_dyn_buf_add(struct allocator_cbs allocator)
{
 struct generic_dyn_buf(int) dyn_buf = dyn_buf_create(int, 4, allocator);
 SCOPE(dyn_buf_destroy(&dyn_buf))
 {
  int tmp = 1;
  dyn_buf_add(dyn_buf, tmp);

  dyn_buf_add(dyn_buf, 2);
  dyn_buf_add(dyn_buf, 2);
  dyn_buf_add(dyn_buf, 2);
  dyn_buf_add(dyn_buf, 2);
  dyn_buf_add(dyn_buf, 2);

  const int* const ref_begin = dyn_buf_begin(dyn_buf);
  const int* begin = dyn_buf_begin(dyn_buf);
  const int* const end = dyn_buf_end(dyn_buf);
  for(;begin < end; begin++) {
   if(begin == ref_begin) {
    assert(*begin == 1);
   } else {
    assert(*begin == 2);
   }
  }
 }
}

//--------------------------------------------------
void test_common_dyn_buf_sort(struct allocator_cbs allocator)
{
 struct generic_dyn_buf(int) dyn_buf = dyn_buf_create(int, 4, allocator);
 SCOPE(dyn_buf_destroy(&dyn_buf))
 {
  dyn_buf_add(dyn_buf, 4);
  dyn_buf_add(dyn_buf, 5);
  dyn_buf_add(dyn_buf, 1);
  dyn_buf_add(dyn_buf, 7);
  dyn_buf_add(dyn_buf, 8);
  dyn_buf_add(dyn_buf, 2);
  dyn_buf_add(dyn_buf, 3);
  dyn_buf_add(dyn_buf, 0);
  dyn_buf_add(dyn_buf, 9);
  dyn_buf_add(dyn_buf, 6);
  generic_dyn_buf_sort(dyn_buf);

  const int* begin = dyn_buf_begin(dyn_buf);
  const int* const end = dyn_buf_end(dyn_buf);
  int test = 0;
  for(;begin < end; test++,  begin++) {
   assert(*begin == test);
  }
 }
}

//--------------------------------------------------
void test_common_dyn_buf(struct allocator_cbs allocator)
{
 test_common_dyn_buf_add(allocator);
 test_common_dyn_buf_sort(allocator);



}
