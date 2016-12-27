#include "array.h"

#include "test/test.h"

#include <stdlib.h>
#include <assert.h>

void internal_dynamic_array_uint_reserve(DynamicArrayUInt* array,
                                         unsigned int capacity_append) {
  assert(array);
  array->capacity += capacity_append;
  array->value = realloc(array->value, sizeof(unsigned int) * array->capacity);
}

const unsigned int DYNAMIC_ARRAY_CAPACITY_INIT = 4;

DynamicArrayUInt* dynamic_array_uint_malloc() {
  DynamicArrayUInt* array = malloc(sizeof(DynamicArrayUInt));
  array->capacity = 0;
  array->size = 0;

  internal_dynamic_array_uint_reserve(array, DYNAMIC_ARRAY_CAPACITY_INIT);

  return array;
}

void dynamic_array_uint_free(DynamicArrayUInt* array) {
  assert(array);
  free(array->value);
  free(array);
}

void dynamic_array_uint_push_back(DynamicArrayUInt* array,
                                  unsigned int value_to_add) {
  assert(array);
  if (array->capacity == array->size) {
    internal_dynamic_array_uint_reserve(array, array->capacity * 2);
  }
  array->value[array->size++] = value_to_add;
}

unsigned int* dynamic_array_uint_get_begin(DynamicArrayUInt* array) {
  assert(array);
  return array->value;
}

unsigned int* dynamic_array_uint_get_end(DynamicArrayUInt* array) {
  assert(array);
  return array->value + array->size;
}

#ifdef INCLUDE_RUN_TEST
int array_test_run()
{
  unsigned int test_values[20] = {2,      51231, 11,  1458, 202, 109,  8,
                                      984998, 65,    348, 631,  15,  6665, 17,
                                      0,      6694,  468, 88,   64,  99};

  DynamicArrayUInt* array = dynamic_array_uint_malloc();
  for (unsigned int i = 0; i < 20; ++i) {
    dynamic_array_uint_push_back(array, test_values[i]);
  }

  unsigned int* it = dynamic_array_uint_get_begin(array);
  unsigned int* end = dynamic_array_uint_get_end(array);
  for (unsigned int i = 0; it != end; ++it, ++i) {
    TEST_ASSERT_EQUAL_UINT(*it, test_values[i]);
  }

  dynamic_array_uint_free(array);
  array = 0x0;

  return 0;
}
#endif // INCLUDE_RUN_TEST
