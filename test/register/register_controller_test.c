#include <check.h>
#include "../../src/register/register_controller.h"

START_TEST(get_a_register_and_have_the_default_value) {
    ck_assert_int_eq(register_array[A], 0);
}
END_TEST

START_TEST(set_a_register_with_an_8_bit_value) {
    register_array[A] = 15;
    ck_assert_int_eq(register_array[A], 15);
}
END_TEST

START_TEST(set_a_register_with_an_16_bit_value) {
    register_array[A] = 0xFFA;
    ck_assert_int_eq(register_array[A], 0xFA);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* register_controller_suite(void) {
    Suite* suite;

    suite = suite_create("Register Controller");

    char* test_names[TEST_CASE_SIZE] = {
        "get_a_register_and_have_the_default_value",
        "set_a_register_with_an_8_bit_value",
        "set_a_register_with_an_16_bit_value"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        get_a_register_and_have_the_default_value,
        set_a_register_with_an_8_bit_value,
        set_a_register_with_an_16_bit_value
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