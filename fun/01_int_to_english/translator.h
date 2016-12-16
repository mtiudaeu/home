#ifndef TRANSLATOR_H
#define TRANSLATOR_H

void translate_int_to_english(unsigned int input, char output[], unsigned int length);

#ifdef INCLUDE_RUN_TEST
int translate_test_run();
#endif // INCLUDE_RUN_TEST

#endif // TRANSLATOR_H
