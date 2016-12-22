#include "test_include.h"

#include <stdio.h>
#include <stdlib.h>

void internal_print_file(const char* filename)
{
  FILE* f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  unsigned int fsize = ftell(f);
  fseek(f, 0, SEEK_SET);  // same as rewind(f);

  char* string = malloc(fsize + 1);
  fread(string, fsize, 1, f);
  fclose(f);

  string[fsize] = 0;

  printf("%s\n", string);
  free(string);
  string = 0x0;
}

void test_include_hello() { printf("hello hello!!\n"); }

void test_include_io()
{
  FILE *file = fopen("triangle.f.glsl", "rb");
  if (!file) {
    printf("cannot open file\n");
    return;
  }
  while (!feof(file)) {
    char c = fgetc(file);
    if (c != EOF) {
      putchar(c);
    }
  }
  fclose(file);
  return;
}

void test_include_io_2()
{
  internal_print_file("triangle.f.glsl");
  internal_print_file("triangle.v.glsl");
}
