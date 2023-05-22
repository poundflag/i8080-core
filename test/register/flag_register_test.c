#include <check.h>
#include "../../src/register/flag_register.h"

START_TEST(set_the_carry_to_true) {
    bool result = check_flag_statement(CARRY, 0xFF, 1, false, '+');
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_carry_to_false) {
    bool result = check_flag_statement(CARRY, 1, 1, false, '+');
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_parity_to_true) {
    bool result = check_flag_statement(PARITY, 0b11110000, 0, false, '+');
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_parity_to_true_1) {
    bool result = check_flag_statement(PARITY, 0x99, 0, false, '+');
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_parity_to_false) {
    bool result = check_flag_statement(PARITY, 0, 0b11110010, false, '+');
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_auxiliary_to_true) {
    bool result = check_flag_statement(AUXILIARY, 0xF, 0xF, false, '+');
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_auxiliary_to_false) {
    bool result = check_flag_statement(AUXILIARY, 1, 1, false, '+');
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_zero_to_true) {
    bool result = check_flag_statement(ZERO, 0, 0, false, '+');
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_zero_to_false) {
    bool result = check_flag_statement(ZERO, 1, 1, false, '+');
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_signed_to_true) {
    bool result = check_flag_statement(SIGNED, 0b10000000, 0, false, '+');
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(set_the_signed_to_false) {
    bool result = check_flag_statement(SIGNED, 0b01000000, 0, false, '+');
    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(set_the_bit_for_the_flag) {
    set_flag_status(CARRY, true);
    ck_assert_int_eq(get_flag_status(CARRY), 1);

    set_flag_status(AUXILIARY, false);
    ck_assert_int_eq(get_flag_status(AUXILIARY), 0);
}
END_TEST

START_TEST(addition_test) {
    ck_assert_int_eq(process_flag_register(0xC9, 0x10, false, '+'), 0b10000010);
    ck_assert_int_eq(process_flag_register(0xA1, 0xC9, false, '+'), 0b00000111);
    ck_assert_int_eq(process_flag_register(0xDE, 0xFE, false, '+'), 0b10010011);
    ck_assert_int_eq(process_flag_register(0xC9, 0x10, false, '+'), 0b10000010);
    ck_assert_int_eq(process_flag_register(0x20, 0x30, false, '+'), 0b00000110);
    ck_assert_int_eq(process_flag_register(0x20, 0x30, false, '+'), 0b00000110);
    ck_assert_int_eq(process_flag_register(0x80, 0x41, false, '+'), 0b10000010);
    ck_assert_int_eq(process_flag_register(0x01, 0xD2, false, '+'), 0b10000010);
}
END_TEST

START_TEST(subtraction_test) {
    printf("AAAAAAA");
    ck_assert_int_eq(process_flag_register(0x23, 0x45, false, '-'), 0b10000111);
    ck_assert_int_eq(process_flag_register(0x00, 0xAA, false, '-'), 0b00000111);
    ck_assert_int_eq(process_flag_register(0x21, 0xDE, false, '-'), 0b00000011);
    ck_assert_int_eq(process_flag_register(0x1, 0x20, false, '-'), 0b10010111);
    ck_assert_int_eq(process_flag_register(0x23, 0xFE, false, '-'), 0b00000011);
    ck_assert_int_eq(process_flag_register(0x11, 0x11, false, '-'), 0b01010110);
    ck_assert_int_eq(process_flag_register(0xDE, 0xFE, false, '-'), 0b10000011);
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
        "set_the_bit_for_the_flag"
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
        set_the_bit_for_the_flag
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