#include "instruction/instruction.h"
#include "register/register_controller.h"
#include "unity.h"

void test_getDestinationRegister_returns_the_valid_index() {
    TEST_ASSERT_EQUAL_INT(REG_B, get_destination_register(0x00));
    TEST_ASSERT_EQUAL_INT(REG_B, get_destination_register(0x07));
    TEST_ASSERT_EQUAL_INT(REG_C, get_destination_register(0x08));
    TEST_ASSERT_EQUAL_INT(REG_C, get_destination_register(0x0F));

    TEST_ASSERT_EQUAL_INT(REG_B, get_destination_register(0x40));
    TEST_ASSERT_EQUAL_INT(REG_B, get_destination_register(0x47));
    TEST_ASSERT_EQUAL_INT(REG_C, get_destination_register(0x48));
    TEST_ASSERT_EQUAL_INT(REG_C, get_destination_register(0x4F));

    TEST_ASSERT_EQUAL_INT(REG_D, get_destination_register(0x50));
    TEST_ASSERT_EQUAL_INT(REG_D, get_destination_register(0x57));
    TEST_ASSERT_EQUAL_INT(REG_E, get_destination_register(0x58));
    TEST_ASSERT_EQUAL_INT(REG_E, get_destination_register(0x5F));

    TEST_ASSERT_EQUAL_INT(REG_H, get_destination_register(0x60));
    TEST_ASSERT_EQUAL_INT(REG_H, get_destination_register(0x67));
    TEST_ASSERT_EQUAL_INT(REG_L, get_destination_register(0x68));
    TEST_ASSERT_EQUAL_INT(REG_L, get_destination_register(0x6F));

    TEST_ASSERT_EQUAL_INT(REG_M, get_destination_register(0x70));
    TEST_ASSERT_EQUAL_INT(REG_M, get_destination_register(0x77));
    TEST_ASSERT_EQUAL_INT(REG_A, get_destination_register(0x78));
    TEST_ASSERT_EQUAL_INT(REG_A, get_destination_register(0x7F));
}

void test_getSourceRegister_returns_the_valid_index() {
    TEST_ASSERT_EQUAL_INT(REG_B, get_source_register(0x40));
    TEST_ASSERT_EQUAL_INT(REG_C, get_source_register(0x41));
    TEST_ASSERT_EQUAL_INT(REG_D, get_source_register(0x42));
    TEST_ASSERT_EQUAL_INT(REG_E, get_source_register(0x43));
    TEST_ASSERT_EQUAL_INT(REG_H, get_source_register(0x44));
    TEST_ASSERT_EQUAL_INT(REG_L, get_source_register(0x45));
    TEST_ASSERT_EQUAL_INT(REG_M, get_source_register(0x46));
    TEST_ASSERT_EQUAL_INT(REG_A, get_source_register(0x47));

    TEST_ASSERT_EQUAL_INT(REG_B, get_source_register(0x48));
    TEST_ASSERT_EQUAL_INT(REG_C, get_source_register(0x49));
    TEST_ASSERT_EQUAL_INT(REG_D, get_source_register(0x4A));
    TEST_ASSERT_EQUAL_INT(REG_E, get_source_register(0x4B));
    TEST_ASSERT_EQUAL_INT(REG_H, get_source_register(0x4C));
    TEST_ASSERT_EQUAL_INT(REG_L, get_source_register(0x4D));
    TEST_ASSERT_EQUAL_INT(REG_M, get_source_register(0x4E));
    TEST_ASSERT_EQUAL_INT(REG_A, get_source_register(0x4F));
}

void run_instruction_test() {
    printf("Instruction:\n");
    RUN_TEST(test_getDestinationRegister_returns_the_valid_index);
    RUN_TEST(test_getSourceRegister_returns_the_valid_index);
}