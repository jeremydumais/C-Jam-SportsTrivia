#include "unity.h"

void runPlayerTests();

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();
    runPlayerTests();
    return UNITY_END();
}
