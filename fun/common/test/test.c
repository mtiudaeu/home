#ifdef INCLUDE_RUN_TEST

#include <stdio.h>
#include <string.h>

#include "test/test.h"


void test_assert_equal_str(const char* a, const char* b, const char* file_name,
                           int line) {
  if (strcmp(a, b) != 0) {
    printf("Error : %s:%d\n", file_name, line);
    printf("   \"%s\" != \"%s\"\n", a, b);
  } else {
    printf("Success\n");
  }
}

void test_assert_equal_uint(unsigned int a, unsigned int b,
                            const char* file_name, int line) {
  if (a != b) {
    printf("Error : %s:%d\n", file_name, line);
    printf("   %d != %d\n", a, b);
  } else {
    printf("Success\n");
  }
}

void test_assert_true_ptr(void* a, const char* file_name, int line)
{
  if (!a) {
    printf("Error : %s:%d\n", file_name, line);
    printf("   Should be true : %p", a);
  } else {
    printf("Success\n");
  }

}


void test_assert_msg(const char* msg, const char* file_name, int line) {
  printf("Error : %s:%d\n", file_name, line);
  printf("   %s", msg);
}

#endif // INCLUDE_RUN_TEST
