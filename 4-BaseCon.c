#include "munit/munit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DECIMAL_TO_BASE 1
#define BASE_TO_DECIMAL 2

int executeUnitTests(int argc, char *argv[]);

int evaluate(char input);
int convertToDecimal(char *input, int base);

char reEvaluate(int input);
void stringReverse(char *str);
char *convertToBase(int base, int inputNum);

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("\nPLEAE USE '--help' FOR HELP\n\n");
    return 1;
  }

  if (argc == 2 && !strcmp(argv[argc - 1], "--help")) {
    printf("\n\nThere are two options <1/2>\n");
    printf("\n1) When converting from decimal to any base (option 1) the "
           "format is <num_in_decimal> <desired_base> <option_1>\n");
    printf("\n2) When converting from any base to decimal (option 2) the "
           "format is <num_in_any_base> "
           "<base_of_num> <option_2>\n");
    printf("\nFor admin use '--run-tests' to run tests\n\n");
    return 1;
  }

  if (argc == 2 && !strcmp(argv[argc - 1], "--run-tests"))
    return executeUnitTests(argc - 1, argv);

  if (argc < 3 ||
      (atoi(argv[3]) != DECIMAL_TO_BASE && atoi(argv[3]) != BASE_TO_DECIMAL)) {
    fprintf(stderr,
            "\n%s %s %s %s Usage: <num> <base> "
            "<desired_conversion> (1 for decimal to any base, and 2 for any "
            "base to decimal)\n",
            argv[0], argv[1], argv[2], argv[3]);
    printf("\n\nUse flag '--help' for help\n\n");

    return 1;
  }

  if (atoi(argv[3]) == DECIMAL_TO_BASE) {
    printf("\nThe number %s in base 10 is %s in base %s\n", argv[1],
           convertToBase(atoi(argv[2]), atoi(argv[1])), argv[2]);
    printf("\n\nUse flag '--help' for help\n\n");
  }

  if (atoi(argv[3]) == BASE_TO_DECIMAL) {
    printf("\nThe number %s in base %s is %d in base 10\n", argv[1], argv[2],
           convertToDecimal(argv[1], atoi(argv[2])));
    printf("\n\nUse flag '--help' for help\n\n");
  }

  return 0;
}

int evaluate(char input) {
  if (input >= '0' && input <= '9')
    return (int)input - '0';
  else
    return (int)input - 'A' + 10;
}

int convertToDecimal(char *input, int base) {

  int power = 1;
  int result = 0;

  for (int idx = strlen(input) - 1; idx >= 0; idx--) {
    if (evaluate(input[idx]) >= base) {
      return -1;
      printf("Invalid Number");
      exit(-1);
    }

    result += evaluate(input[idx]) * power;
    power = power * base;
  }

  return result;
}

char reEvaluate(int input) {
  if (input >= 0 && input <= 9)
    return (char)(input + '0');
  else
    return (char)(input - 10 + 'A');
}

void stringReverse(char *string) {
  int len = strlen(string);
  int i;
  for (i = 0; i < len / 2; i++) {
    char temp = string[i];
    string[i] = string[len - i - 1];
    string[len - i - 1] = temp;
  }
}

char *convertToBase(int base, int inputNum) {
  int index = 0;
  char result[100];

  while (inputNum > 0) {
    result[index++] = reEvaluate(inputNum % base);
    inputNum /= base;
  }
  result[index] = '\0';

  stringReverse(result);

  return result;
}

static MunitResult convertToBaseTest(const MunitParameter params[],
                                     void *data) {
  char result[100];
  munit_assert_true(strcmp(convertToBase(16, 282), "11A") == 0);
  munit_assert_true(strcmp(convertToBase(16, 3941), "F65") == 0);
  munit_assert_true(strcmp(convertToBase(2, 1), "1") == 0);
  munit_assert_true(strcmp(convertToBase(2, 3941), "111101100101") == 0);
  munit_assert_true(strcmp(convertToBase(10, 10), "10") == 0);
  munit_assert_true(strcmp(convertToBase(32, 32), "10") == 0);
  return MUNIT_OK;
}

static MunitResult convertToDecimalTest(const MunitParameter params[],
                                        void *data) {
  munit_assert_true(convertToDecimal("11A", 16) == 282);
  munit_assert_true(convertToDecimal("0F65", 16) == 3941);
  munit_assert_true(convertToDecimal("0001", 2) == 1);
  munit_assert_true(convertToDecimal("111101100101", 2) == 3941);
  munit_assert_true(convertToDecimal("32", 32) == 98);

  return MUNIT_OK;
}

MunitTest tests[] = {{"/decimalToBase", convertToBaseTest, NULL, NULL,
                      MUNIT_TEST_OPTION_NONE, NULL},
                     {"/baseToDecimal", convertToDecimalTest, NULL, NULL,
                      MUNIT_TEST_OPTION_NONE, NULL},
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite primaryTestSuite = {"/primary", tests, NULL, 1,
                                            MUNIT_SUITE_OPTION_NONE};

int executeUnitTests(int argc, char *argv[]) {
  return munit_suite_main(&primaryTestSuite, NULL, argc, argv);
}
