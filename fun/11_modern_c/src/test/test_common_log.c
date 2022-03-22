#include "test/test_common_log.h"

#include "common/str.h"
#include "common/log.h"


//--------------------
void test_common_log_run(struct allocator_cbs allocator)
{
 print("%s:%s:%s", "test", "hey", "sup");
 print("hey : %d",1131);
 print_fd(2, "hey : %d",1131);
 print_fd(2, "\n");

 LOG_ERROR("Testing the Error Logging, do not worry : %d", 1337);
}
