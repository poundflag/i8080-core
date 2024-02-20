#include "register/register_controller.h"
#include "unity.h"

void test_get_a_register_and_have_the_default_value() { TEST_ASSERT_EQUAL_INT(0, get_register(REG_A)); }

void test_set_a_register_with_an_8_bit_value() {
    set_register(REG_A, 15);
    TEST_ASSERT_EQUAL_INT(15, get_register(REG_A));
}

void test_set_a_register_with_an_16_bit_value() {
    set_register(REG_A, 0xFFA);
    TEST_ASSERT_EQUAL_INT(0xFA, get_register(REG_A));
}

void test_get_a_register_pair_and_have_the_default_value() { TEST_ASSERT_EQUAL_INT(0, get_register_pair(PAIR_B)); }

void test_set_a_register_pair() {
    set_register_pair(PAIR_D, 0x1234);
    TEST_ASSERT_EQUAL_INT(0x1234, get_register_pair(PAIR_D));
    TEST_ASSERT_EQUAL_INT(0x12, get_register(REG_D));
    TEST_ASSERT_EQUAL_INT(0x34, get_register(REG_E));
}

void test_get_a_program_counter_and_have_the_default_value() { TEST_ASSERT_EQUAL_INT(0, get_program_counter()); }

void test_set_the_program_counter() {
    set_program_counter(10);
    TEST_ASSERT_EQUAL_INT(10, get_program_counter());
}

void test_increment_the_program_counter() {
    increment_program_counter();
    TEST_ASSERT_EQUAL_INT(1, get_program_counter());
}

void test_have_the_default_flag_value() { TEST_ASSERT_EQUAL_INT(0b00000010, get_register(REG_F)); }

void test_set_the_bit_for_the_register() {
    set_register_bit(REG_A, 2, true);
    TEST_ASSERT_EQUAL_INT(true, get_register_bit(REG_A, 2));
    TEST_ASSERT_EQUAL_INT(0b00000100, get_register(REG_A));

    set_register_bit(REG_B, 2, false);
    TEST_ASSERT_EQUAL_INT(false, get_register_bit(REG_B, 2));
    TEST_ASSERT_EQUAL_INT(0b00000000, get_register(REG_B));
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