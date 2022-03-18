#include "test/test_common_str.h"

#include "common/allocator_cbs.h"
#include "common/str.h"

#include <unistd.h>
#include <stdlib.h>

static allocator_cbs allocator =
{
 .malloc=&malloc,
 .realloc=&realloc,
 .free=&free
};

void test_common_str_run()
{
 write(1, "hey\n", 4);

 str_buf str_buf = str_buf_create(10, allocator);
 str_buf = str_buf_destroy(str_buf);
}
