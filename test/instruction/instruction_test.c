#include "../../src/instruction/instruction.h"
#include "../../src/register/register_controller.h"
#include "unity.h"

void test_getDestinationRegister_returns_the_valid_index() {
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x00), REG_B);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x07), REG_B);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x08), REG_C);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x0F), REG_C);

  TEST_ASSERT_EQUAL_INT(get_destination_register(0x40), REG_B);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x47), REG_B);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x48), REG_C);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x4F), REG_C);

  TEST_ASSERT_EQUAL_INT(get_destination_register(0x50), REG_D);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x57), REG_D);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x58), REG_E);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x5F), REG_E);

  TEST_ASSERT_EQUAL_INT(get_destination_register(0x60), REG_H);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x67), REG_H);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x68), REG_L);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x6F), REG_L);

  TEST_ASSERT_EQUAL_INT(get_destination_register(0x70), REG_M);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x77), REG_M);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x78), REG_A);
  TEST_ASSERT_EQUAL_INT(get_destination_register(0x7F), REG_A);
}

void test_getSourceRegister_returns_the_valid_index() {
  TEST_ASSERT_EQUAL_INT(get_source_register(0x40), REG_B);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x41), REG_C);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x42), REG_D);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x43), REG_E);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x44), REG_H);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x45), REG_L);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x46), REG_M);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x47), REG_A);

  TEST_ASSERT_EQUAL_INT(get_source_register(0x48), REG_B);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x49), REG_C);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x4A), REG_D);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x4B), REG_E);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x4C), REG_H);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x4D), REG_L);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x4E), REG_M);
  TEST_ASSERT_EQUAL_INT(get_source_register(0x4F), REG_A);
}

void run_instruction_test() {
  printf("Instruction:\n");
  RUN_TEST(test_getDestinationRegister_returns_the_valid_index);
  RUN_TEST(test_getSourceRegister_returns_the_valid_index);
}