#include <check.h>
#include "../../src/register/flag_register.h"

START_TEST(set_the_carry_to_true) {
    ck_assert_int_eq(is_result_carry(0xFF + 1), 1);
}
END_TEST

START_TEST(set_the_carry_to_false) {
    ck_assert_int_eq(is_result_carry(1 + 1), 0);
}
END_TEST

START_TEST(set_the_parity_to_true) {
    ck_assert_int_eq(is_result_parity(0b11110000), 1);
}
END_TEST

START_TEST(set_the_parity_to_true_1) {
    ck_assert_int_eq(is_result_parity(0x99), 1);
}
END_TEST

START_TEST(set_the_parity_to_false) {
    ck_assert_int_eq(is_result_parity(0b11110010), 0);
}
END_TEST

START_TEST(set_the_auxiliary_to_true) {
    ck_assert_int_eq(is_result_auxiliary_carry(0xF, 0xF, PLUS_OPERATION), 1);
}
END_TEST

START_TEST(set_the_auxiliary_to_false) {
    ck_assert_int_eq(is_result_auxiliary_carry(1, 1, PLUS_OPERATION), 0);
}
END_TEST

START_TEST(set_the_zero_to_true) {
    ck_assert_int_eq(is_result_zero(0), 1);
}
END_TEST

START_TEST(set_the_zero_to_false) {
    ck_assert_int_eq(is_result_zero(2), 0);
}
END_TEST

START_TEST(set_the_signed_to_true) {
    ck_assert_int_eq(is_result_signed(0b10000000), 1);
}
END_TEST

START_TEST(set_the_signed_to_false) {
    ck_assert_int_eq(is_result_signed(0b01000000), 0);
}
END_TEST

START_TEST(addition_test) {
    ck_assert_int_eq(process_flag_register(0xC9, 0x10, PLUS_OPERATION), 0b10000010);
    ck_assert_int_eq(process_flag_register(0xA1, 0xC9, PLUS_OPERATION), 0b00000111);
    ck_assert_int_eq(process_flag_register(0xDE, 0xFE, PLUS_OPERATION), 0b10010011);
    ck_assert_int_eq(process_flag_register(0xC9, 0x10, PLUS_OPERATION), 0b10000010);
    ck_assert_int_eq(process_flag_register(0x20, 0x30, PLUS_OPERATION), 0b00000110);
    ck_assert_int_eq(process_flag_register(0x20, 0x30, PLUS_OPERATION), 0b00000110);
    ck_assert_int_eq(process_flag_register(0x80, 0x41, PLUS_OPERATION), 0b10000010);
    ck_assert_int_eq(process_flag_register(0x01, 0xD2, PLUS_OPERATION), 0b10000010);
}
END_TEST

START_TEST(subtraction_test) {
    ck_assert_int_eq(process_flag_register(0x23, 0x45, SUBTRACTION_OPERATION), 0b10000111);
    ck_assert_int_eq(process_flag_register(0x00, 0xAA, SUBTRACTION_OPERATION), 0b00000111);
    ck_assert_int_eq(process_flag_register(0x21, 0xDE, SUBTRACTION_OPERATION), 0b00000011);
    ck_assert_int_eq(process_flag_register(0x1, 0x20, SUBTRACTION_OPERATION), 0b10010111);
    ck_assert_int_eq(process_flag_register(0x23, 0xFE, SUBTRACTION_OPERATION), 0b00000011);
    ck_assert_int_eq(process_flag_register(0x11, 0x11, SUBTRACTION_OPERATION), 0b01010110);
    ck_assert_int_eq(process_flag_register(0xDE, 0xFE, SUBTRACTION_OPERATION), 0b10000011);
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
        "set the signed to false",
        "test the addition",
        "test the subtraction",
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
        addition_test,
        subtraction_test,
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