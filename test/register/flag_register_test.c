#include "../../src/register/flag_register.h"
#include "unity.h"

void test_set_the_carry_to_true() {
  TEST_ASSERT_EQUAL_INT(is_result_carry(0xFF + 1), 1);
}

void test_set_the_carry_to_false() {
  TEST_ASSERT_EQUAL_INT(is_result_carry(1 + 1), 0);
}

void test_set_the_parity_to_true() {
  TEST_ASSERT_EQUAL_INT(is_result_parity(0b11110000), 1);
}

void test_set_the_parity_to_true_1() {
  TEST_ASSERT_EQUAL_INT(is_result_parity(0x99), 1);
}

void test_set_the_parity_to_false() {
  TEST_ASSERT_EQUAL_INT(is_result_parity(0b11110010), 0);
}

void test_set_the_auxiliary_to_true() {
  TEST_ASSERT_EQUAL_INT(is_result_auxiliary_carry(0xF, 0xF, PLUS_OPERATION), 1);
}

void test_set_the_auxiliary_to_false() {
  TEST_ASSERT_EQUAL_INT(is_result_auxiliary_carry(1, 1, PLUS_OPERATION), 0);
}

void test_set_the_zero_to_true() {
  TEST_ASSERT_EQUAL_INT(is_result_zero(0), 1);
}

void test_set_the_zero_to_false() {
  TEST_ASSERT_EQUAL_INT(is_result_zero(2), 0);
}

void test_set_the_signed_to_true() {
  TEST_ASSERT_EQUAL_INT(is_result_signed(0b10000000), 1);
}

void test_set_the_signed_to_false() {
  TEST_ASSERT_EQUAL_INT(is_result_signed(0b01000000), 0);
}

void test_addition_test() {
  TEST_ASSERT_EQUAL_INT(process_flag_register(0xC9, 0x10, PLUS_OPERATION),
                        0b10000010);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0xA1, 0xC9, PLUS_OPERATION),
                        0b00000111);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0xDE, 0xFE, PLUS_OPERATION),
                        0b10010011);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0xC9, 0x10, PLUS_OPERATION),
                        0b10000010);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0x20, 0x30, PLUS_OPERATION),
                        0b00000110);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0x20, 0x30, PLUS_OPERATION),
                        0b00000110);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0x80, 0x41, PLUS_OPERATION),
                        0b10000010);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0x01, 0xD2, PLUS_OPERATION),
                        0b10000010);
}

void test_subtraction_test() {
  TEST_ASSERT_EQUAL_INT(
      process_flag_register(0x23, 0x45, SUBTRACTION_OPERATION), 0b10000111);
  TEST_ASSERT_EQUAL_INT(
      process_flag_register(0x00, 0xAA, SUBTRACTION_OPERATION), 0b00000111);
  TEST_ASSERT_EQUAL_INT(
      process_flag_register(0x21, 0xDE, SUBTRACTION_OPERATION), 0b00000011);
  TEST_ASSERT_EQUAL_INT(process_flag_register(0x1, 0x20, SUBTRACTION_OPERATION),
                        0b10010111);
  TEST_ASSERT_EQUAL_INT(
      process_flag_register(0x23, 0xFE, SUBTRACTION_OPERATION), 0b00000011);
  TEST_ASSERT_EQUAL_INT(
      process_flag_register(0x11, 0x11, SUBTRACTION_OPERATION), 0b01010110);
  TEST_ASSERT_EQUAL_INT(
      process_flag_register(0xDE, 0xFE, SUBTRACTION_OPERATION), 0b10000011);
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