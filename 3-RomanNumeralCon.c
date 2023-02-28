#include "munit/munit.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int execute_unit_tests(int argc, char *argv[]);

static int singleCharConversion(char currentNumeral) {
  switch (currentNumeral) {
  case 'i':
    return 1;
  case 'v':
    return 5;
  case 'x':
    return 10;
  case 'l':
    return 50;
  case 'c':
    return 100;
  case 'd':
    return 500;
  case 'm':
    return 1000;
  case 'V':
    return 5000;
  case 'X':
    return 10000;
  case 'L':
    return 50000;
  case 'C':
    return 100000;
  case 'D':
    return 500000;
  case 'M':
    return 1000000;
  default:
    return -1;
    printf("Invalid input, please try again.\n");
    printf("Remember to use uppercase only for barred numerals, and only use "
           "valid characters.\n");
    exit(-1);
  }
}

int romanToInt(char *input) {
  int idx, Total = singleCharConversion(input[0]);

  for (idx = 1; input[idx] != '\0'; idx++) {
    int prevNum = singleCharConversion(input[idx - 1]);
    int currNum = singleCharConversion(input[idx]);
    if (prevNum < currNum) {
      Total = Total - prevNum + (currNum - prevNum);
    } else {
      Total += currNum;
    }
  }
  return Total;
}

int main(int argc, char *argv[]) {
  if (argc == 2 && !strcmp(argv[argc - 1], "--run-tests"))
    return execute_unit_tests(argc - 1, argv);

  int total = 0;
  char *input = argv[1];
  printf("Roman to integer: %d\n", romanToInt(input));

  return 0;
}

static MunitResult test_conversion(const MunitParameter params[], void *data) {
  munit_assert_true(romanToInt("ii") == 2);
  munit_assert_true(romanToInt("xxxvii") == 37);
  munit_assert_true(romanToInt("cxxxvi") == 136);
  munit_assert_true(romanToInt("M") == 1000000);
  return MUNIT_OK;
}

static MunitResult invalid_input(const MunitParameter params[], void *data) {
  munit_assert_true(singleCharConversion('a') == -1);
  munit_assert_true(singleCharConversion('%') == -1);
  return MUNIT_OK;
}

MunitTest tests[] = {
    {"/conversions", test_conversion, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/invalid_input", invalid_input, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite primary_test_suite = {"/primary", tests, NULL, 1,
                                              MUNIT_SUITE_OPTION_NONE};

int execute_unit_tests(int argc, char *argv[]) {
  return munit_suite_main(&primary_test_suite, NULL, argc, argv);
}