#include "translator.h"

#include "test.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void internal_cat_str(char* str, const char* add, unsigned int length) {
  if (!str) {
    return;
  }
  if (*str != 0) {  // add space
    strcat(str, " ");
  }
  // FIXME add two str len to make sure we don't overflow length.
  strcat(str, add);
}

void internal_print_digit(unsigned int input, char output[],
                          unsigned int length) {
  {  // input validation
    if (input >= 10) {
      return;  // invalid input
    }
    if (input == 0) {
      return;  // nothing to output
    }
  }

  static const char* digits_str[] = {"zero", "one", "two",   "three", "four",
                                     "five", "six", "seven", "eight", "nine"};
  internal_cat_str(output, digits_str[input], length);
}

void internal_print_tens(unsigned int input, char output[],
                         unsigned int length) {
  {  // input validation
    if (input >= 100) {
      return;  // invalid input
    }
    if (input == 0) {
      return;  // nothing to output
    }
  }

  if (input < 10) {
    internal_print_digit(input, output, length);
    return;
  }
  if (input < 20) {
    static const char* under_20_str[] = {
        "ten",       "eleven",  "twelve",    "thirteen", "fourteen",
        "fifthteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    internal_cat_str(output, under_20_str[input-10], length);
    return;
  }
  else {
    static const char * above_and_equal_20_str [] = {"twenty", "thirty", "forty",
                                               "fifty",  "sixty",  "seventy",
                                               "eighty", "ninety"};
    internal_cat_str(output, above_and_equal_20_str[(input/10)-2], length);
    internal_print_digit(input % 10, output, length);
  }
}

void internal_print_hundred(unsigned int input, char output[],
                            unsigned int length) {
  {  // input validation
    if (input >= 1000) {
      return;  // invalid input
    }
    if (input == 0) {
      return;  // nothing to output
    }
  }

  const unsigned int digit_hundred = input / 100;
  if ( digit_hundred ) {
    internal_print_digit(digit_hundred, output, length);
    internal_cat_str(output, "hundred", length);
  }

  internal_print_tens(input % 100, output, length);
}

void translate_int_to_english(unsigned int input, char output[], unsigned int length) {
  if (input == 0) { // only case the zero str will be displayed
    internal_cat_str(output, "zero", length);
  }

  const unsigned int nb_million = input / 1000000;
  if ( nb_million ) {
    internal_print_hundred(nb_million, output, length);
    internal_cat_str(output, "million", length);
  }

  input %= 1000000;
  const unsigned int nb_thousand = input / 1000;
  if ( nb_thousand ) {
    internal_print_hundred(nb_thousand, output, length);
    internal_cat_str(output, "thousand", length);
  }

  input %= 1000;
  internal_print_hundred(input, output, length);
}

#ifdef INCLUDE_RUN_TEST
int translate_test_run() {
  { // test global functionality
    unsigned int size = 100;
    char value[100];

    translate_int_to_english(0, value, size);
    TEST_ASSERT_EQUAL_STR(value, "zero");
    strcpy(value, "");

    translate_int_to_english(10, value, size);
    TEST_ASSERT_EQUAL_STR(value, "ten");
    strcpy(value, "");

    translate_int_to_english(121, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one hundred twenty one");
    strcpy(value, "");

    translate_int_to_english(1032, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one thousand thirty two");
    strcpy(value, "");

    translate_int_to_english(11043, value, size);
    TEST_ASSERT_EQUAL_STR(value, "eleven thousand forty three");
    strcpy(value, "");

    translate_int_to_english(1200000, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one million two hundred thousand");
    strcpy(value, "");
  }

  {
    const unsigned int size = 100;
    char value[100] = "";

    internal_print_digit(1, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one");
    strcpy(value, "");

    internal_print_digit(2, value, size);
    TEST_ASSERT_EQUAL_STR(value, "two");
    strcpy(value, "");

    internal_print_digit(3, value, size);
    TEST_ASSERT_EQUAL_STR(value, "three");
    strcpy(value, "");

    internal_print_digit(4, value, size);
    TEST_ASSERT_EQUAL_STR(value, "four");
    strcpy(value, "");

    internal_print_digit(5, value, size);
    TEST_ASSERT_EQUAL_STR(value, "five");
    strcpy(value, "");

    internal_print_digit(6, value, size);
    TEST_ASSERT_EQUAL_STR(value, "six");
    strcpy(value, "");

    internal_print_digit(7, value, size);
    TEST_ASSERT_EQUAL_STR(value, "seven");
    strcpy(value, "");

    internal_print_digit(8, value, size);
    TEST_ASSERT_EQUAL_STR(value, "eight");
    strcpy(value, "");

    internal_print_digit(9, value, size);
    TEST_ASSERT_EQUAL_STR(value, "nine");
    strcpy(value, "");

    internal_print_digit(10, value, size); // stays the same
    TEST_ASSERT_EQUAL_STR(value, "");
    strcpy(value, "");

    internal_print_digit(0, value, size); // stays the same
    TEST_ASSERT_EQUAL_STR(value, "");
    strcpy(value, "");
  }

  {
    const unsigned int size = 100;
    char value[100] = "";

    internal_print_tens(1, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one");
    strcpy(value, "");

    internal_print_tens(10, value, size);
    TEST_ASSERT_EQUAL_STR(value, "ten");
    strcpy(value, "");

    internal_print_tens(11, value, size);
    TEST_ASSERT_EQUAL_STR(value, "eleven");
    strcpy(value, "");

    internal_print_tens(12, value, size);
    TEST_ASSERT_EQUAL_STR(value, "twelve");
    strcpy(value, "");

    internal_print_tens(13, value, size);
    TEST_ASSERT_EQUAL_STR(value, "thirteen");
    strcpy(value, "");

    internal_print_tens(14, value, size);
    TEST_ASSERT_EQUAL_STR(value, "fourteen");
    strcpy(value, "");

    internal_print_tens(15, value, size);
    TEST_ASSERT_EQUAL_STR(value, "fifthteen");
    strcpy(value, "");

    internal_print_tens(16, value, size);
    TEST_ASSERT_EQUAL_STR(value, "sixteen");
    strcpy(value, "");

    internal_print_tens(17, value, size);
    TEST_ASSERT_EQUAL_STR(value, "seventeen");
    strcpy(value, "");

    internal_print_tens(18, value, size);
    TEST_ASSERT_EQUAL_STR(value, "eighteen");
    strcpy(value, "");

    internal_print_tens(19, value, size); // stays the same
    TEST_ASSERT_EQUAL_STR(value, "nineteen");
    strcpy(value, "");

    internal_print_tens(20, value, size); // stays the same
    TEST_ASSERT_EQUAL_STR(value, "twenty");
    strcpy(value, "");

    internal_print_tens(21, value, size); // stays the same
    TEST_ASSERT_EQUAL_STR(value, "twenty one");
    strcpy(value, "");

    internal_print_tens(97, value, size); // stays the same
    TEST_ASSERT_EQUAL_STR(value, "ninety seven");
    strcpy(value, "");

  }

  {
    const unsigned int size = 100;
    char value[100] = "";

    internal_print_hundred(1, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one");
    strcpy(value, "");

    internal_print_hundred(10, value, size);
    TEST_ASSERT_EQUAL_STR(value, "ten");
    strcpy(value, "");

    internal_print_hundred(100, value, size);
    TEST_ASSERT_EQUAL_STR(value, "one hundred");
    strcpy(value, "");

    internal_print_hundred(934, value, size);
    TEST_ASSERT_EQUAL_STR(value, "nine hundred thirty four");
    strcpy(value, "");
  }
  return 0;
}
#endif // INCLUDE_RUN_TEST
