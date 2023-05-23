#include <check.h>
#include "../../src/register/register_controller.h"

START_TEST(get_a_register_and_have_the_default_value) {
    ck_assert_int_eq(get_register(REG_A), 0);
}
END_TEST

START_TEST(set_a_register_with_an_8_bit_value) {
    set_register(REG_A, 15);
    ck_assert_int_eq(get_register(REG_A), 15);
}
END_TEST

START_TEST(set_a_register_with_an_16_bit_value) {
    set_register(REG_A, 0xFFA);
    ck_assert_int_eq(get_register(REG_A), 0xFA);
}
END_TEST

START_TEST(get_a_register_pair_and_have_the_default_value) {
    ck_assert_int_eq(get_register_pair(PAIR_B), 0);
}
END_TEST

START_TEST(set_a_register_pair) {
    set_register_pair(PAIR_D, 0x1234);
    ck_assert_int_eq(get_register_pair(PAIR_D), 0x1234);
    ck_assert_int_eq(get_register(REG_D), 0x34);
    ck_assert_int_eq(get_register(REG_E), 0x12);
}
END_TEST

START_TEST(get_a_program_counter_and_have_the_default_value) {
    ck_assert_int_eq(get_program_counter(), 0);
}
END_TEST

START_TEST(set_the_program_counter) {
    set_program_counter(10);
    ck_assert_int_eq(get_program_counter(), 10);
}
END_TEST

START_TEST(increment_the_program_counter) {
    increment_program_counter();
    ck_assert_int_eq(get_program_counter(), 1);
}
END_TEST

START_TEST(have_the_default_flag_value) {
    ck_assert_int_eq(get_register(REG_F), 0b00000010);
}
END_TEST

START_TEST(set_the_bit_for_the_register) {
    set_register_bit(REG_A, 2, true);
    ck_assert_int_eq(get_register_bit(REG_A, 2), true);
    ck_assert_int_eq(get_register(REG_A), 0b00000100);

    set_register_bit(REG_B, 2, false);
    ck_assert_int_eq(get_register_bit(REG_B, 2), false);
    ck_assert_int_eq(get_register(REG_B), 0b00000000);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* register_controller_suite(void) {
    Suite* suite;

    suite = suite_create("Register Controller");

    char* test_names[TEST_CASE_SIZE] = {
        "get_a_register_and_have_the_default_value",
        "set_a_register_with_an_8_bit_value",
        "set_a_register_with_an_16_bit_value",
        "get_a_register_pair_and_have_the_default_value",
        "set_a_register_pair",
        "get_a_program_counter_and_have_the_default_value",
        "set_the_program_counter",
        "increment_the_program_counter",
        "have_the_default_flag_value",
        "set_the_bit_for_the_register"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        get_a_register_and_have_the_default_value,
        set_a_register_with_an_8_bit_value,
        set_a_register_with_an_16_bit_value,
        get_a_register_pair_and_have_the_default_value,
        set_a_register_pair,
        get_a_program_counter_and_have_the_default_value,
        set_the_program_counter,
        increment_the_program_counter,
        have_the_default_flag_value,
        set_the_bit_for_the_register
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