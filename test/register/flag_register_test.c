#include "register/flag_register.h"
#include "unity.h"

void test_set_the_carry_to_true() { TEST_ASSERT_TRUE(is_result_carry(0xFF + 1)); }

void test_set_the_carry_to_false() { TEST_ASSERT_FALSE(is_result_carry(1 + 1)); }

void test_set_the_parity_to_true() { TEST_ASSERT_TRUE(is_result_parity(0b11110000)); }

void test_set_the_parity_to_true_1() { TEST_ASSERT_TRUE(is_result_parity(0x99)); }

void test_set_the_parity_to_false() { TEST_ASSERT_FALSE(is_result_parity(0b11110010)); }

void test_set_the_auxiliary_to_true() { TEST_ASSERT_TRUE(is_result_auxiliary_carry(0xF, 0xF, 0)); }

void test_set_the_auxiliary_to_false() { TEST_ASSERT_FALSE(is_result_auxiliary_carry(1, 1, 0)); }

void test_set_the_zero_to_true() { TEST_ASSERT_TRUE(is_result_zero(0)); }

void test_set_the_zero_to_false() { TEST_ASSERT_FALSE(is_result_zero(2)); }

void test_set_the_signed_to_true() { TEST_ASSERT_TRUE(is_result_signed(0b10000000)); }

void test_set_the_signed_to_false() { TEST_ASSERT_FALSE(is_result_signed(0b01000000)); }

void test_addition_test() {
    TEST_ASSERT_EQUAL_INT(0b10000010, process_flag_register(0xC9, 0x10, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b00000111, process_flag_register(0xA1, 0xC9, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b10010011, process_flag_register(0xDE, 0xFE, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b10000010, process_flag_register(0xC9, 0x10, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b00000110, process_flag_register(0x20, 0x30, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b00000110, process_flag_register(0x20, 0x30, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b10000010, process_flag_register(0x80, 0x41, 0, PLUS_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b10000010, process_flag_register(0x01, 0xD2, 0, PLUS_OPERATION));
}

void test_subtraction_test() {
    TEST_ASSERT_EQUAL_INT(0b10000111, process_flag_register(0x23, 0x45, 0, SUBTRACTION_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b00000111, process_flag_register(0x00, 0xAA, 0, SUBTRACTION_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b00000011, process_flag_register(0x21, 0xDE, 0, SUBTRACTION_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b10010111, process_flag_register(0x1, 0x20, 0, SUBTRACTION_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b00000011, process_flag_register(0x23, 0xFE, 0, SUBTRACTION_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b01010110, process_flag_register(0x11, 0x11, 0, SUBTRACTION_OPERATION));
    TEST_ASSERT_EQUAL_INT(0b10000011, process_flag_register(0xDE, 0xFE, 1, SUBTRACTION_OPERATION));
}

void run_flag_register_test() {
    printf("Flag register:\n");
    RUN_TEST(test_set_the_carry_to_true);
    RUN_TEST(test_set_the_carry_to_false);
    RUN_TEST(test_set_the_parity_to_true);
    RUN_TEST(test_set_the_parity_to_true_1);
    RUN_TEST(test_set_the_parity_to_false);
    RUN_TEST(test_set_the_auxiliary_to_true);
    RUN_TEST(test_set_the_auxiliary_to_false);
    RUN_TEST(test_set_the_zero_to_true);
    RUN_TEST(test_set_the_zero_to_false);
    RUN_TEST(test_set_the_signed_to_true);
    RUN_TEST(test_set_the_signed_to_false);
    RUN_TEST(test_addition_test);
    RUN_TEST(test_subtraction_test);
}