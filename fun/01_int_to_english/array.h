#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
  unsigned int capacity;
  unsigned int size;
  unsigned int* value;
} DynamicArrayUInt;

DynamicArrayUInt* dynamic_array_uint_malloc();
void dynamic_array_uint_free(DynamicArrayUInt* array);

void dynamic_array_uint_push_back(DynamicArrayUInt* array,
                                  unsigned int value_to_add);

unsigned int * dynamic_array_uint_get_begin(DynamicArrayUInt* array);
unsigned int * dynamic_array_uint_get_end(DynamicArrayUInt* array);

#ifdef INCLUDE_RUN_TEST
int array_test_run();
#endif // INCLUDE_RUN_TEST

#endif // ARRAY_H
