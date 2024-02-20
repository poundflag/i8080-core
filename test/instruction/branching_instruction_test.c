#include "bus_controller.h"
#include "instruction/branching_instruction.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "register/stack.h"
#include "unity.h"
#include <stdbool.h>

void test_jmp_test() {
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x34);
    write_to_memory(2, 0x12);
    set_program_counter(0);

    bool result = jmp(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(0x34, temporary_address);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x34, get_data_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = jmp(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x12, get_data_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = jmp(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1233, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0, get_data_bus());
    TEST_ASSERT_TRUE(result);
}

void test_jmp_conditional_true() {
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x34);
    write_to_memory(2, 0x12);
    set_program_counter(0);
    set_register_bit(REG_F, CARRY, true);

    bool result = jmp_conditional(0, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x34, temporary_address);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = jmp_conditional(1, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = jmp_conditional(2, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1233, get_address_bus());
    TEST_ASSERT_TRUE(result);
}

void test_jmp_conditional_false() {
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x34);
    write_to_memory(2, 0x12);
    set_program_counter(0);
    set_register_bit(REG_F, CARRY, false);

    bool result = jmp_conditional(0, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x34, temporary_address);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = jmp_conditional(1, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = jmp_conditional(2, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_TRUE(result);
}

void test_call_test() {
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x34);
    write_to_memory(2, 0x12);
    set_program_counter(0);
    set_stack_pointer(10);

    bool result = call(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(0x34, temporary_address);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = call(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = call(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1233, get_address_bus());
    TEST_ASSERT_EQUAL_INT(3, pull_word());
    TEST_ASSERT_TRUE(result);
}

void test_call_conditional_true() {
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x34);
    write_to_memory(2, 0x12);
    set_program_counter(0);
    set_stack_pointer(10);
    set_register_bit(REG_F, CARRY, true);

    bool result = call_conditional(0, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x34, temporary_address);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = call_conditional(1, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = call_conditional(2, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(0x1233, get_address_bus());
    TEST_ASSERT_EQUAL_INT(3, pull_word());
    TEST_ASSERT_TRUE(result);
}

void test_call_conditional_false() {
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x34);
    write_to_memory(2, 0x12);
    set_program_counter(0);
    set_stack_pointer(10);
    set_register_bit(REG_F, CARRY, false);

    bool result = call_conditional(0, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x34, temporary_address);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = call_conditional(1, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(result, false);

    result = call_conditional(2, &temporary_address, COND_CARRY);
    TEST_ASSERT_EQUAL_INT(0x1234, temporary_address);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0, pull_word());
    TEST_ASSERT_TRUE(result);
}

void test_ret_test() {
    set_stack_pointer(10);
    push_word(3);

    bool result = ret();
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_TRUE(result);
}

void test_ret_conditional_true() {
    set_stack_pointer(10);
    push_word(3);
    set_register_bit(REG_F, CARRY, true);

    bool result = ret_conditional(CARRY);
    TEST_ASSERT_EQUAL_INT(2, get_address_bus());
    TEST_ASSERT_TRUE(result);
}

void test_ret_conditional_false() {
    set_stack_pointer(10);
    push_word(3);
    set_register_bit(REG_F, CARRY, false);

    bool result = ret_conditional(CARRY);
    TEST_ASSERT_EQUAL_INT(0, get_address_bus());
    TEST_ASSERT_TRUE(result);
}

void test_pchl_test() {
    set_register_pair(PAIR_H, 0x1234);
    bool result = pchl();
    TEST_ASSERT_EQUAL_INT(0x1234, get_register_pair(PAIR_H));
    TEST_ASSERT_EQUAL_INT(0x1233, get_address_bus());
    TEST_ASSERT_TRUE(result);
}

void run_branching_instruction_test() {
    printf("Branching instruction:\n");
    RUN_TEST(test_jmp_test);
    RUN_TEST(test_jmp_conditional_true);
    RUN_TEST(test_jmp_conditional_false);
    RUN_TEST(test_call_test);
    RUN_TEST(test_call_conditional_true);
    RUN_TEST(test_call_conditional_false);
    RUN_TEST(test_ret_test);
    RUN_TEST(test_ret_conditional_true);
    RUN_TEST(test_ret_conditional_false);
    RUN_TEST(test_pchl_test);
}