#include "common/test.h"
#include "common/allocator_cbs.h"

#include "test/test_common_str.h"
#include "test/test_common_log.h"

#include <stdlib.h>

static allocator_cbs allocator =
{
 .malloc=&malloc,
 .realloc=&realloc,
 .free=&free
};

//--------------------------------------------------------------------------------
int main() {

test_common_str_run(allocator);
test_common_log_run(allocator);

}
