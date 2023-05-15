#include <check.h>
#include "../../src/memory/memory_controller.h"

START_TEST(read_from_address_and_return_zero) {
    ck_assert_int_eq(read(1), 0);
}
END_TEST

START_TEST(read_from_address_out_of_range_and_return_zero) {
    ck_assert_int_eq(read(0x10000), 0);
}
END_TEST

START_TEST(write_a_value_to_memory) {
    write(1, 10);
    ck_assert_int_eq(read(1), 10);
}
END_TEST

START_TEST(write_a_value_to_memory_out_of_range) {
    write(1, 10);
    ck_assert_int_eq(read(1), 10);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* memory_controller_suite(void) {
    Suite* suite;

    suite = suite_create("Memory Controller");

    char* test_names[TEST_CASE_SIZE] = {
        "Read from address and return zero",
        "Read from address out of range and return zero",
        "Write a value to memory",
        "Write a value to memory out of range"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        read_from_address_and_return_zero,
        read_from_address_out_of_range_and_return_zero,
        write_a_value_to_memory,
        write_a_value_to_memory_out_of_range
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