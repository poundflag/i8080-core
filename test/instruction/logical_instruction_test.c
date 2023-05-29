#include <check.h>
#include <stdbool.h>
#include "../../src/instruction/logical_instruction.h"
#include "../../src/instruction/instruction.h"
#include "../../src/register/register_controller.h"
#include "../../src/register/stack.h"
#include "../../src/memory/memory_controller.h"

START_TEST(mov_test) {
    set_register(REG_A, 10);
    mov(REG_B, REG_A);

    ck_assert_int_eq(get_register(REG_B), 10);
    ck_assert_int_eq(get_register(REG_A), 10);
}
END_TEST

START_TEST(mvi_test) {
    set_program_counter(0);
    bool result = false;
    write(1, 50);

    result = mvi(REG_B, 0);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(result, false);

    result = mvi(REG_B, 1);
    ck_assert_int_eq(get_register(REG_B), 50);
    ck_assert_int_eq(get_register(REG_B), read(1));
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(lxi_test) {
    set_program_counter(0);
    bool result = false;
    write(1, 0x12);
    write(2, 0x34);

    result = lxi(PAIR_B, 0);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0);
    ck_assert_int_eq(result, 0);

    result = lxi(PAIR_B, 1);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0x1200);
    ck_assert_int_eq(result, 0);

    result = lxi(PAIR_B, 2);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0x1234);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(lda_test) {
    set_program_counter(0);
    bool result = false;
    uint16_t temporary_address = 0;
    write(1, 0x10);
    write(2, 0x00);
    write(0x0010, 55);

    result = lda(0, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, 0);

    result = lda(1, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, 0);

    result = lda(2, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, 0);

    result = lda(3, &temporary_address);
    ck_assert_int_eq(get_register(REG_A), 55);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(sta_test) {
    set_program_counter(0);
    bool result = false;
    uint16_t temporary_address = 0;
    write(1, 0x10);
    write(2, 0x00);
    set_register(REG_A, 55);

    result = sta(0, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(read(0x0010), 0);
    ck_assert_int_eq(result, 0);

    result = sta(1, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(read(0x0010), 0);
    ck_assert_int_eq(result, 0);

    result = sta(2, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(read(0x0010), 0);
    ck_assert_int_eq(result, 0);

    result = sta(3, &temporary_address);
    ck_assert_int_eq(get_register(REG_A), 55);
    ck_assert_int_eq(read(0x0010), 55);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(lhld_test) {
    bool result = false;
    uint16_t temporary_address = 0;
    write(1, 0x10);
    write(2, 0x00);
    write(0x0010, 0x12);
    write(0x0011, 0x34);

    result = lhld(0, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0);

    result = lhld(1, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0);

    result = lhld(2, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0);

    result = lhld(3, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 0x0011);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0x1200);

    result = lhld(4, &temporary_address);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0x1234);
}
END_TEST

START_TEST(shld_test) {
    bool result = false;
    uint16_t temporary_address = 0;
    write(1, 0x10);
    write(2, 0x00);
    set_register_pair(PAIR_H, 0x1234);

    result = shld(0, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 1);

    result = shld(1, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 2);

    result = shld(2, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(temporary_address, 2);

    result = shld(3, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 0x0011);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(read(0x0010), 0x12);
    ck_assert_int_eq(read(0x0011), 0x00);

    result = shld(4, &temporary_address);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(read(0x0010), 0x12);
    ck_assert_int_eq(read(0x0011), 0x34);
}
END_TEST

START_TEST(ldax_test) {
    bool result = false;
    uint16_t temporary_address = 0;
    write(0x0010, 74);
    set_register_pair(PAIR_B, 0x0010);

    result = ldax(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(get_register(REG_A), 0);

    result = ldax(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 0);
    ck_assert_int_eq(get_register(REG_A), 74);
}
END_TEST

START_TEST(stax_test) {
    bool result = false;
    uint16_t temporary_address = 0;
    set_register(REG_A, 74);
    set_register_pair(PAIR_B, 0x0010);

    result = stax(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(read(0x0010), 0);

    result = stax(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 0);
    ck_assert_int_eq(read(0x0010), 74);
}
END_TEST

START_TEST(xchg_test) {
    bool result = false;
    set_register_pair(PAIR_D, 0x1111);
    set_register_pair(PAIR_H, 0x4444);

    result = xchg();
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_register_pair(PAIR_D), 0x4444);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0x1111);
    ck_assert_int_eq(get_program_counter(), 0);
}
END_TEST

START_TEST(rst_test) {
    bool result = rst(1);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 7);
    ck_assert_int_eq(pull_word(), 1);

    result = rst(2);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 15);
    ck_assert_int_eq(pull_word(), 8);
}
END_TEST

START_TEST(push_test) {
    set_register_pair(PAIR_B, 0x1234);
    set_stack_pointer(10);
    uint16_t temporary_address = 0;

    bool result = push(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 9);

    result = push(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 8);

    result = push(PAIR_B, 2, &temporary_address);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 0);
    ck_assert_int_eq(pull_word(), 0x1234);
}
END_TEST

START_TEST(pop_test) {
    set_stack_pointer(10);
    push_word(0x1234);
    uint16_t temporary_address = 0;

    bool result = pop(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 7);

    result = pop(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(result, false);
    ck_assert_int_eq(get_program_counter(), 6);

    result = pop(PAIR_B, 2, &temporary_address);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_program_counter(), 0);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0x1234);
}
END_TEST

START_TEST(xthl_test) {
    push_word(0x5678);
    set_register_pair(PAIR_H, 0x1234);

    bool result = xthl();
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0x5678);
    ck_assert_int_eq(pull_word(), 0x1234);
}
END_TEST

START_TEST(sphl_test) {
    set_register_pair(PAIR_H, 0x1234);

    bool result = sphl();
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_stack_pointer(), 0x1234);
}
END_TEST

START_TEST(in_test) {
    bool result = in(1);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(out_test) {
    bool result = out(1);
    ck_assert_int_eq(result, true);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* logical_instruction_suite(void) {
    Suite* suite;

    suite = suite_create("Logical Instruction");

    char* test_names[TEST_CASE_SIZE] = {
        "MOV",
        "MVI",
        "LXI",
        "LDA",
        "STA",
        "LHLD",
        "SHLD",
        "LDAX",
        "STAX",
        "XCHG",
        "RST",
        "PUSH",
        "POP",
        "XTHL",
        "SPHL",
        "IN",
        "OUT"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        mov_test,
        mvi_test,
        lxi_test,
        lda_test,
        sta_test,
        lhld_test,
        shld_test,
        ldax_test,
        stax_test,
        xchg_test,
        rst_test,
        push_test,
        pop_test,
        xthl_test,
        sphl_test,
        in_test,
        out_test
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