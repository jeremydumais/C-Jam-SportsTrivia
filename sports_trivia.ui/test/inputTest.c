#include "input.h"
#include "unity.h"

void getChoosenNumberFromKey_WithZeroKeyOutsideScope_ReturnMinusOne() 
{
    TEST_ASSERT_EQUAL_INT(-1, getChoosenNumberFromKey(SDLK_0, 1, 5));
}

void getChoosenNumberFromKey_WithZeroKeyInsideScope_ReturnZero() 
{
    TEST_ASSERT_EQUAL_INT(0, getChoosenNumberFromKey(SDLK_0, 0, 5));
}

void getChoosenNumberFromKey_WithOneKeyInsideScope_ReturnOne() 
{
    TEST_ASSERT_EQUAL_INT(1, getChoosenNumberFromKey(SDLK_1, 0, 5));
}

void getChoosenNumberFromKey_WithFiveKeyInsideScope_ReturnFive() 
{
    TEST_ASSERT_EQUAL_INT(1, getChoosenNumberFromKey(SDLK_1, 0, 5));
}

void getChoosenNumberFromKey_WithNineKeyInsideScope_ReturnNine() 
{
    TEST_ASSERT_EQUAL_INT(9, getChoosenNumberFromKey(SDLK_9, 5, 9));
}

void getChoosenNumberFromKey_WithNineKeyOutsideScope_ReturnMinusOne() 
{
    TEST_ASSERT_EQUAL_INT(-1, getChoosenNumberFromKey(SDLK_9, 5, 7));
}

void getChoosenNumberFromKey_WithOneKeypadOutsideScope_ReturnMinusOne() 
{
    TEST_ASSERT_EQUAL_INT(-1, getChoosenNumberFromKey(SDLK_KP_1, 5, 7));
}

void getChoosenNumberFromKey_WithOneKeypadInsideScope_ReturnOne() 
{
    TEST_ASSERT_EQUAL_INT(1, getChoosenNumberFromKey(SDLK_KP_1, 1, 7));
}

void getChoosenNumberFromKey_WithSevenKeypadInsideScope_ReturnSeven() 
{
    TEST_ASSERT_EQUAL_INT(7, getChoosenNumberFromKey(SDLK_KP_7, 1, 7));
}

void getChoosenNumberFromKey_WithNineKeypadOutsideScope_ReturnMinusOne() 
{
    TEST_ASSERT_EQUAL_INT(-1, getChoosenNumberFromKey(SDLK_KP_9, 1, 7));
}

void getChoosenNumberFromKey_WithNineKeypadInsideScope_ReturnNine() 
{
    TEST_ASSERT_EQUAL_INT(9, getChoosenNumberFromKey(SDLK_KP_9, 5, 9));
}

void getChoosenNumberFromKey_WithZeroKeypadOutsideScope_ReturnMinusOne() 
{
    TEST_ASSERT_EQUAL_INT(-1, getChoosenNumberFromKey(SDLK_KP_0, 5, 9));
}

void getChoosenNumberFromKey_WithZeroKeypadInsideScope_ReturnZero() 
{
    TEST_ASSERT_EQUAL_INT(0, getChoosenNumberFromKey(SDLK_KP_0, 0, 4));
}


void runinputTests()
{
    RUN_TEST(getChoosenNumberFromKey_WithZeroKeyOutsideScope_ReturnMinusOne);
    RUN_TEST(getChoosenNumberFromKey_WithZeroKeyInsideScope_ReturnZero);
    RUN_TEST(getChoosenNumberFromKey_WithOneKeyInsideScope_ReturnOne);
    RUN_TEST(getChoosenNumberFromKey_WithFiveKeyInsideScope_ReturnFive);
    RUN_TEST(getChoosenNumberFromKey_WithNineKeyInsideScope_ReturnNine);
    RUN_TEST(getChoosenNumberFromKey_WithNineKeyOutsideScope_ReturnMinusOne);
    RUN_TEST(getChoosenNumberFromKey_WithOneKeypadOutsideScope_ReturnMinusOne);
    RUN_TEST(getChoosenNumberFromKey_WithOneKeypadInsideScope_ReturnOne);
    RUN_TEST(getChoosenNumberFromKey_WithSevenKeypadInsideScope_ReturnSeven);
    RUN_TEST(getChoosenNumberFromKey_WithNineKeypadOutsideScope_ReturnMinusOne);
    RUN_TEST(getChoosenNumberFromKey_WithNineKeypadInsideScope_ReturnNine);
    RUN_TEST(getChoosenNumberFromKey_WithZeroKeypadOutsideScope_ReturnMinusOne);
    RUN_TEST(getChoosenNumberFromKey_WithZeroKeypadInsideScope_ReturnZero);
}