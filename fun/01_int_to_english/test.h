#ifndef TEST_H
#define TEST_H

#define TEST_ASSERT_EQUAL_STR(a, b) \
  test_assert_equal_str(a, b, __FILE__, __LINE__);
void test_assert_equal_str(const char* a, const char* b, const char* file_name,
                           int line);

#define TEST_ASSERT_EQUAL_UINT(a, b) \
  test_assert_equal_uint(a, b, __FILE__, __LINE__);
void test_assert_equal_uint(unsigned int a, unsigned int b,
                            const char* file_name, int line);

#define TEST_ASSERT_MSG(msg) \
  test_assert_msg(msg, __FILE__, __LINE__);
void test_assert_msg(const char* msg, const char* file_name, int line);

#endif  // TEST_H
