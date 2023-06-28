#include "../../src/register/register_controller.h"
#include "unity.h"

void test_get_a_register_and_have_the_default_value() { TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0); }

void test_set_a_register_with_an_8_bit_value() {
    set_register(REG_A, 15);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 15);
}

void test_set_a_register_with_an_16_bit_value() {
    set_register(REG_A, 0xFFA);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0xFA);
}

void test_get_a_register_pair_and_have_the_default_value() { TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_B), 0); }

void test_set_a_register_pair() {
    set_register_pair(PAIR_D, 0x1234);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_D), 0x1234);
    TEST_ASSERT_EQUAL_INT(get_register(REG_D), 0x12);
    TEST_ASSERT_EQUAL_INT(get_register(REG_E), 0x34);
}

void test_get_a_program_counter_and_have_the_default_value() { TEST_ASSERT_EQUAL_INT(get_program_counter(), 0); }

void test_set_the_program_counter() {
    set_program_counter(10);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 10);
}

void test_increment_the_program_counter() {
    increment_program_counter();
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
}

void test_have_the_default_flag_value() { TEST_ASSERT_EQUAL_INT(get_register(REG_F), 0b00000010); }

void test_set_the_bit_for_the_register() {
    set_register_bit(REG_A, 2, true);
    TEST_ASSERT_EQUAL_INT(get_register_bit(REG_A, 2), true);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0b00000100);

    set_register_bit(REG_B, 2, false);
    TEST_ASSERT_EQUAL_INT(get_register_bit(REG_B, 2), false);
    TEST_ASSERT_EQUAL_INT(get_register(REG_B), 0b00000000);
}

void run_register_controller_test() {
    printf("Register controller test:\n");
    RUN_TEST(test_get_a_register_and_have_the_default_value);
    RUN_TEST(test_set_a_register_with_an_8_bit_value);
    RUN_TEST(test_set_a_register_with_an_16_bit_value);
    RUN_TEST(test_get_a_register_pair_and_have_the_default_value);
    RUN_TEST(test_set_a_register_pair);
    RUN_TEST(test_get_a_program_counter_and_have_the_default_value);
    RUN_TEST(test_set_the_program_counter);
    RUN_TEST(test_increment_the_program_counter);
    RUN_TEST(test_have_the_default_flag_value);
    RUN_TEST(test_set_the_bit_for_the_register);
}