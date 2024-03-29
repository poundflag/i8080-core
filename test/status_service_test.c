#include "cpu.h"
#include "instruction/logical_instruction.h"
#include "memory/memory_controller.h"
#include "status_service.h"
#include "unity.h"

void test_be_true_when_stack_is_accessed() {
    uint16_t temporary_address = 0;
    TEST_ASSERT_EQUAL_INT(false, is_stack_access());

    push(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_stack_access());
    push(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_stack_access());
    push(PAIR_B, 2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_stack_access());

    pop(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_stack_access());
    pop(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_stack_access());
    pop(PAIR_B, 2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_stack_access());
}

void test_be_false_when_memory_is_not_read() {
    uint16_t temporary_address = 0;
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());

    sta(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());
    sta(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());
    sta(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_memory_read());
    sta(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());

    shld(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());
    shld(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());
    shld(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_memory_read());
    shld(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_memory_read());
    shld(4, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());

    stax(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_memory_read());
    stax(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());

    push(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_memory_read());
    push(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_memory_read());
    push(PAIR_B, 2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_memory_read());
}

void test_be_true_when_first_machine_cycle() {
    uint16_t temporary_address = 0;
    int machine_cycle = 0;
    write_to_memory(1, 0xC6);
    step(&machine_cycle, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_first_machine_cycle());

    step(&machine_cycle, &temporary_address); // Read opcode
    TEST_ASSERT_EQUAL_INT(false, is_first_machine_cycle());
    step(&machine_cycle,
         &temporary_address); // Execute with immediate value in addr. 1
    TEST_ASSERT_EQUAL_INT(true, is_first_machine_cycle());
}

void test_be_false_when_write_output() {
    uint16_t temporary_address = 0;
    TEST_ASSERT_EQUAL_INT(true, is_write_output());

    sta(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());
    sta(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());
    sta(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    sta(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());

    shld(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());
    shld(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());
    shld(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    shld(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    shld(4, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());

    stax(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    stax(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());

    push(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    push(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    push(PAIR_B, 2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(true, is_write_output());
}

void test_be_true_when_output_device() {
    out(0);
    TEST_ASSERT_EQUAL_INT(false, is_device_output());
    TEST_ASSERT_EQUAL_INT(false, !is_write_output());
    out(1);
    TEST_ASSERT_EQUAL_INT(true, is_device_output());
    TEST_ASSERT_EQUAL_INT(false, is_write_output());
    out(2);
    TEST_ASSERT_EQUAL_INT(false, is_device_output());
    TEST_ASSERT_EQUAL_INT(false, !is_write_output());
}

void test_be_true_when_input_device() {
    in(0);
    TEST_ASSERT_EQUAL_INT(false, is_device_input());
    in(1);
    TEST_ASSERT_EQUAL_INT(true, is_device_input());
    in(2);
    TEST_ASSERT_EQUAL_INT(false, is_device_input());
}

void test_be_true_when_system_halts() {
    TEST_ASSERT_EQUAL_INT(false, has_system_halted());
    hlt();
    TEST_ASSERT_EQUAL_INT(true, has_system_halted());
}

void run_status_service_test() {
    printf("Status Service:\n");
    RUN_TEST(test_be_true_when_stack_is_accessed);
    RUN_TEST(test_be_false_when_memory_is_not_read);
    RUN_TEST(test_be_true_when_first_machine_cycle);
    RUN_TEST(test_be_false_when_write_output);
    RUN_TEST(test_be_true_when_output_device);
    RUN_TEST(test_be_true_when_input_device);
    RUN_TEST(test_be_true_when_system_halts);
}