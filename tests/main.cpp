#include <mintest/suit.h>
#include "tests.h"

int main(void) {
    TestSuit TS;
    register_tests(TS);
    TS.run_tests();
    return 0;
}

