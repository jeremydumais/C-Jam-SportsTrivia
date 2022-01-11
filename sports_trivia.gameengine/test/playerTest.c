#include "player.h"
#include "unity.h"
#include <stdlib.h>

void getPlayerScoreAsString_WithZero_ReturnZeroString() 
{
    char *actual = getPlayerScoreAsString(0);
    TEST_ASSERT_EQUAL_STRING("0", actual);
    free(actual);
}

void getPlayerScoreAsString_WithOne_ReturnOneString() 
{
    char *actual = getPlayerScoreAsString(1);
    TEST_ASSERT_EQUAL_STRING("1", actual);
    free(actual);
}

void getPlayerScoreAsString_With123_Return123String() 
{
    char *actual = getPlayerScoreAsString(123);
    TEST_ASSERT_EQUAL_STRING("123", actual);
    free(actual);
}

void runPlayerTests()
{
    RUN_TEST(getPlayerScoreAsString_WithZero_ReturnZeroString);
    RUN_TEST(getPlayerScoreAsString_WithOne_ReturnOneString);
    RUN_TEST(getPlayerScoreAsString_With123_Return123String);
}