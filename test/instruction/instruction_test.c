#include <check.h>
#include "../../src/instruction/instruction.h"

START_TEST(getDestinationIndex_returns_the_valid_index) {
    ck_assert_int_eq(getDestinationIndex(0x40), 0);
    ck_assert_int_eq(getDestinationIndex(0x47), 0);
}
END_TEST

START_TEST(getSourceIndex_returns_the_valid_index) {
    ck_assert_int_eq(getSourceIndex(0x0), 0);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* instruction_suite(void) {
    Suite* suite;

    suite = suite_create("Instruction");

    char* test_names[TEST_CASE_SIZE] = {
        "getDestinationIndex returns the valid index",
        "getSourceIndex returns the valid index"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        getDestinationIndex_returns_the_valid_index,
        getSourceIndex_returns_the_valid_index

    };

    for (int i = 0; i < TEST_CASE_SIZE; i++) {
        // Create a new test case for each iteration
        TCase* test_case = tcase_create(test_names[i]);

        // Add the corresponding test function based on the index
        tcase_add_test(test_case, test_functions[i]);

        // Add the test case to the suite
        suite_add_tcase(suite, test_case);
    }

    return suite;
}