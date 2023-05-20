#include <check.h>
#include "../../src/register/flag_register.h"

START_TEST(set_the_carry_to_true) {
    bool result = check_flag_statement(CARRY, 0xFF, 1, false);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_carry_to_false) {
    bool result = check_flag_statement(CARRY, 1, 1, false);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_parity_to_true) {
    bool result = check_flag_statement(PARITY, 0b11110000, 0, false);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_parity_to_true_1) {
    bool result = check_flag_statement(PARITY, 0x99, 0, false);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_parity_to_false) {
    bool result = check_flag_statement(PARITY, 0, 0b11110010, false);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_auxiliary_to_true) {
    bool result = check_flag_statement(AUXILIARY, 0xF, 0xF, false);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_auxiliary_to_false) {
    bool result = check_flag_statement(AUXILIARY, 1, 1, false);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_zero_to_true) {
    bool result = check_flag_statement(ZERO, 0, 0, false);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_zero_to_false) {
    bool result = check_flag_statement(ZERO, 1, 1, false);
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_signed_to_true) {
    bool result = check_flag_statement(SIGNED, 0b10000000, 0, false);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_signed_to_false) {
    bool result = check_flag_statement(SIGNED, 0b01000000, 0, false);
    ck_assert_int_eq(result, 0);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* flag_register_suite(void) {
    Suite* suite;

    suite = suite_create("Flag Register");

    char* test_names[TEST_CASE_SIZE] = {
        "set the carry to true",
        "set the carry to false",
        "set the parity to true",
        "set the parity to true 1",
        "set the parity to false",
        "set the auxiliary to true",
        "set the auxiliary to false",
        "set the zero to true",
        "set the zero to false",
        "set the signed to true",
        "set the signed to false"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        set_the_carry_to_true,
        set_the_carry_to_false,
        set_the_parity_to_true,
        set_the_parity_to_true_1,
        set_the_parity_to_false,
        set_the_auxiliary_to_true,
        set_the_auxiliary_to_false,
        set_the_zero_to_true,
        set_the_zero_to_false,
        set_the_signed_to_true,
        set_the_signed_to_false,
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