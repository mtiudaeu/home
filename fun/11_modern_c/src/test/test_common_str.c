#include "test/test_common_str.h"

#include "common/allocator_cbs.h"
#include "common/str.h"

#include <unistd.h>


void test_common_str_run(allocator_cbs allocator)
{
 str_buf str_buf = str_buf_create(10, allocator);
 str_buf = str_buf_destroy(str_buf);
}
