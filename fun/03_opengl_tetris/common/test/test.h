#ifndef TEST_H
#define TEST_H

#ifdef INCLUDE_RUN_TEST

#define TEST_ASSERT_MSG(msg)                                    \
  printf("Test Error : %s, %s:%d\n", msg, __FILE__, __LINE__); \

#define TEST_ASSERT_TRUE(expr)                                     \
  if (expr) {                                                      \
    printf("Test Success\n");                                      \
  } else {                                                         \
    printf("Test Error : %s, %s:%d\n", #expr, __FILE__, __LINE__); \
  }

#endif // INCLUDE_RUN_TEST

#endif  // TEST_H
