#include <check.h>
#include <stdbool.h>
#include "../../src/instruction/logical_instruction.h"
#include "../../src/instruction/instruction.h"
#include "../../src/register/register_controller.h"
#include "../../src/memory/memory_controller.h"

START_TEST(mov_test) {
    uint8_t source = 10;
    uint8_t destination = 0;
    mov(&destination, source);

    ck_assert_int_eq(destination, source);
    ck_assert_int_eq(destination, 10);
}
END_TEST

START_TEST(mvi_test) {
    uint8_t destination = 0;
    set_program_counter(0);
    bool result = false;
    write(1, 50);

    int machine_cycle = 0;
    result = mvi(&destination, machine_cycle);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(result, false);

    result = machine_cycle = 1;
    mvi(&destination, machine_cycle);
    ck_assert_int_eq(destination, 50);
    ck_assert_int_eq(destination, read(1));
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(lxi_test) {
    set_program_counter(0);
    bool result = false;
    write(1, 0x12);
    write(2, 0x34);

    int machine_cycle = 0;
    result = lxi(PAIR_B, machine_cycle);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 1;
    result = lxi(PAIR_B, machine_cycle);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0x1200);
    ck_assert_int_eq(result, 0);

    machine_cycle = 2;
    result = lxi(PAIR_B, machine_cycle);
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

    int machine_cycle = 0;
    result = lda(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 1;
    result = lda(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 2;
    result = lda(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 3;
    result = lda(machine_cycle, &temporary_address);
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

    int machine_cycle = 0;
    result = sta(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(read(0x0010), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 1;
    result = sta(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(read(0x0010), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 2;
    result = sta(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_program_counter(), 0x0010);
    ck_assert_int_eq(temporary_address, 2);
    ck_assert_int_eq(read(0x0010), 0);
    ck_assert_int_eq(result, 0);

    machine_cycle = 3;
    result = sta(machine_cycle, &temporary_address);
    ck_assert_int_eq(get_register(REG_A), 55);
    ck_assert_int_eq(read(0x0010), 55);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, 1);
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
        "STA"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        mov_test,
        mvi_test,
        lxi_test,
        lda_test,
        sta_test
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