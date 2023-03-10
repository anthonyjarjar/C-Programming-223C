#include "munit/munit.h"
#include "functions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

static MunitResult newLineTest(const MunitParameter params[], void *data)
{
    munit_assert_true(newLineCount("\n\n\n") == 3);
    munit_assert_true(newLineCount("There are\n 3\n newlines\n") == 3);
    munit_assert_true(newLineCount("/\n//n") == 1);
    return MUNIT_OK;
}

static MunitResult byteCountTest(const MunitParameter params[], void *data)
{
    munit_assert_true(byteCount("1234 ") == 5);
    munit_assert_true(byteCount("There are\n 3\n newlines\n") == 23);
    return MUNIT_OK;
}

static MunitResult maxLineLenTest(const MunitParameter params[], void *data)
{
    munit_assert_true(maxLineLen("1234 ") == 5);
    munit_assert_true(maxLineLen("This is the longest line\nThis is not") == 24);
    return MUNIT_OK;
}

static MunitResult wordCountTest(const MunitParameter params[], void *data)
{
    munit_assert_true(wordCount("1234 ") == 1);
    munit_assert_true(wordCount("This is the longest line\nThis is not - ") == 9);
    return MUNIT_OK;
}

static MunitResult includesTest(const MunitParameter params[], void *data)
{
    char *arr[3] = {"-l", "included", "notIN"};
    munit_assert_true(includes(arr, "-l"));
    munit_assert_true(includes(arr, "included"));
    return MUNIT_OK;
}

MunitTest tests[] = {{"/newLineTest", newLineTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/byteCountTest", byteCountTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/maxLineLenTest", maxLineLenTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/wordCountTest", wordCountTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {"/includesTest", includesTest, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
                     {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite primaryTestSuite = {"/primary", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};

int executeUnitTests(int argc, char *argv[])
{
    return munit_suite_main(&primaryTestSuite, NULL, argc, argv);
}

int main(int argc, char *argv[1])
{
    return executeUnitTests(argc, argv);
}
