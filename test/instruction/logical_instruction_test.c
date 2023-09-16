#include "bus_controller.h"
#include "instruction/instruction.h"
#include "instruction/logical_instruction.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "register/stack.h"
#include "unity.h"
#include <stdbool.h>

void test_mov_test() {
    set_register(REG_A, 10);
    mov(REG_B, REG_A);

    TEST_ASSERT_EQUAL_INT(get_register(REG_B), 10);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 10);
}

void test_mvi_test() {
    set_program_counter(0);
    bool result = false;
    write_to_memory(1, 50);

    result = mvi(REG_B, 0);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
    TEST_ASSERT_EQUAL_INT(result, false);

    result = mvi(REG_B, 1);
    TEST_ASSERT_EQUAL_INT(get_register(REG_B), 50);
    TEST_ASSERT_EQUAL_INT(result, true);
}

void test_lxi_test() {
    set_program_counter(0);
    bool result = false;
    write_to_memory(1, 0x12);
    write_to_memory(2, 0x34);

    result = lxi(PAIR_B, 0);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x12);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_B), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = lxi(PAIR_B, 1);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x34);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_B), 0x0012);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = lxi(PAIR_B, 2);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_B), 0x3412);
    TEST_ASSERT_EQUAL_INT(result, 1);
}

void test_lda_test() {
    set_program_counter(0);
    bool result = false;
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x10);
    write_to_memory(2, 0x00);
    write_to_memory(0x0010, 55);

    result = lda(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x10);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = lda(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x00);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = lda(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0010);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 55);
    TEST_ASSERT_EQUAL_INT(temporary_address, 2);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = lda(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 55);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(result, 1);
}

void test_sta_test() {
    set_program_counter(0);
    bool result = false;
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x10);
    write_to_memory(2, 0x00);
    set_register(REG_A, 55);

    result = sta(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x10);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = sta(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x00);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = sta(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0010);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0xFF);
    TEST_ASSERT_EQUAL_INT(temporary_address, 2);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 0);
    TEST_ASSERT_EQUAL_INT(result, 0);

    result = sta(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 55);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 55);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0);
    TEST_ASSERT_EQUAL_INT(result, 1);
}

void test_lhld_test() {
    bool result = false;
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x10);
    write_to_memory(2, 0x00);
    write_to_memory(0x0010, 0x12);
    write_to_memory(0x0011, 0x34);

    result = lhld(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x10);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0);

    result = lhld(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x00);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0);

    result = lhld(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0010);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x12);
    TEST_ASSERT_EQUAL_INT(temporary_address, 2);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0);

    result = lhld(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0011);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x34);
    TEST_ASSERT_EQUAL_INT(temporary_address, 2);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0x0012);

    result = lhld(4, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0x3412);
}

void test_shld_test() {
    bool result = false;
    uint16_t temporary_address = 0;
    write_to_memory(1, 0x10);
    write_to_memory(2, 0x00);
    set_register_pair(PAIR_H, 0x1234);

    result = shld(0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 1);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x10);

    result = shld(1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0x00);

    result = shld(2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0010);
    TEST_ASSERT_EQUAL_INT(temporary_address, 2);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0xFF);

    result = shld(3, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0011);
    TEST_ASSERT_EQUAL_INT(temporary_address, 2);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 0x34);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0011), 0x00);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0xFF);

    result = shld(4, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 2);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 0x34);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0011), 0x12);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0);
}

void test_ldax_test() {
    bool result = false;
    uint16_t temporary_address = 0;
    write_to_memory(0x0010, 74);
    set_register_pair(PAIR_B, 0x0010);

    result = ldax(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0010);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 74);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 0);

    result = ldax(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0);
    TEST_ASSERT_EQUAL_INT(get_register(REG_A), 74);
}

void test_stax_test() {
    bool result = false;
    uint16_t temporary_address = 0;
    set_register(REG_A, 74);
    set_register_pair(PAIR_B, 0x0010);

    result = stax(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0x0010);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 0);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0xFF);

    result = stax(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0);
    TEST_ASSERT_EQUAL_INT(read_from_memory(0x0010), 74);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0);
}

void test_xchg_test() {
    bool result = false;
    set_register_pair(PAIR_D, 0x1111);
    set_register_pair(PAIR_H, 0x4444);

    result = xchg();
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_D), 0x4444);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0x1111);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0);
}

void test_rst_test() {
    bool result = rst(1);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 7);
    TEST_ASSERT_EQUAL_INT(pull_word(), 1);

    result = rst(2);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 15);
    TEST_ASSERT_EQUAL_INT(pull_word(), 8);
}

void test_push_test() {
    set_register_pair(PAIR_B, 0x1234);
    set_stack_pointer(10);
    uint16_t temporary_address = 0;

    bool result = push(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 9);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0xFF);

    result = push(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 8);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0xFF);

    result = push(PAIR_B, 2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0);
    TEST_ASSERT_EQUAL_INT(pull_word(), 0x1234);
    TEST_ASSERT_EQUAL_INT(get_data_bus(), 0);
}

void test_pop_test() { // TODO TEST WITH BUS CONTROLLER LATER
    set_stack_pointer(10);
    push_word(0x1234);
    uint16_t temporary_address = 0;

    bool result = pop(PAIR_B, 0, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 7);

    result = pop(PAIR_B, 1, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, false);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 6);

    result = pop(PAIR_B, 2, &temporary_address);
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_program_counter(), 0);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_B), 0x1234);
}

void test_xthl_test() {
    push_word(0x5678);
    set_register_pair(PAIR_H, 0x1234);

    bool result = xthl();
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_register_pair(PAIR_H), 0x5678);
    TEST_ASSERT_EQUAL_INT(pull_word(), 0x1234);
}

void test_sphl_test() {
    set_register_pair(PAIR_H, 0x1234);

    bool result = sphl();
    TEST_ASSERT_EQUAL_INT(result, true);
    TEST_ASSERT_EQUAL_INT(get_stack_pointer(), 0x1234);
}

void test_in_test() {
    write_to_memory(1, 0x20);

    bool result = in(0);
    TEST_ASSERT_EQUAL_INT(1, get_program_counter());

    result = in(1);
    TEST_ASSERT_EQUAL_INT(0xFE, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0xFE, get_data_bus());
    TEST_ASSERT_EQUAL_INT(0x2020, get_address_bus());

    result = in(2);
    TEST_ASSERT_EQUAL_INT(result, true);
}

void test_out_test() {
    write_to_memory(1, 0x20);

    bool result = out(0);
    TEST_ASSERT_EQUAL_INT(1, get_program_counter());

    result = out(1);
    TEST_ASSERT_EQUAL_INT(0xEE, get_register(REG_B));
    TEST_ASSERT_EQUAL_INT(0xFF, get_data_bus());
    TEST_ASSERT_EQUAL_INT(0x2020, get_address_bus());

    result = out(2);
    TEST_ASSERT_EQUAL_INT(result, true);
}

void run_logical_instruction_test() {
    printf("Logical instruction:\n");
    RUN_TEST(test_mov_test);
    RUN_TEST(test_mvi_test);
    RUN_TEST(test_lxi_test);
    RUN_TEST(test_lda_test);
    RUN_TEST(test_sta_test);
    RUN_TEST(test_lhld_test);
    RUN_TEST(test_shld_test);
    RUN_TEST(test_ldax_test);
    RUN_TEST(test_stax_test);
    RUN_TEST(test_xchg_test);
    RUN_TEST(test_rst_test);
    RUN_TEST(test_push_test);
    RUN_TEST(test_pop_test);
    RUN_TEST(test_xthl_test);
    RUN_TEST(test_sphl_test);
    RUN_TEST(test_in_test);
    RUN_TEST(test_out_test);
}