#include <check.h>
#include <stdbool.h>
#include "../../src/register/register_controller.h"
#include "../../src/memory/memory_controller.h"
#include "../../src/instruction/branching_instruction.h"

START_TEST(jmp_test) {
    uint16_t temporary_address = 0;
    write(1, 0x34);
    write(2, 0x12);
    set_program_counter(0);

    bool result = jmp(0, &temporary_address);
    ck_assert_int_eq(temporary_address, 0x34);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(result, false);

    result = jmp(1, &temporary_address);
    ck_assert_int_eq(temporary_address, 0x1234);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, false);

    result = jmp(2, &temporary_address);
    ck_assert_int_eq(temporary_address, 0x1234);
    ck_assert_int_eq(get_program_counter(), 0x1233);
    ck_assert_int_eq(result, true);

}
END_TEST

START_TEST(jmp_conditional_true) {
    uint16_t temporary_address = 0;
    write(1, 0x34);
    write(2, 0x12);
    set_program_counter(0);
    set_register_bit(REG_F, CARRY, true);

    bool result = jmp_conditional(0, &temporary_address, COND_CARRY);
    ck_assert_int_eq(temporary_address, 0x34);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(result, false);

    result = jmp_conditional(1, &temporary_address, COND_CARRY);
    ck_assert_int_eq(temporary_address, 0x1234);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, false);

    result = jmp_conditional(2, &temporary_address, COND_CARRY);
    ck_assert_int_eq(temporary_address, 0x1234);
    ck_assert_int_eq(get_program_counter(), 0x1233);
    ck_assert_int_eq(result, true);

}
END_TEST

START_TEST(jmp_conditional_false) {
    uint16_t temporary_address = 0;
    write(1, 0x34);
    write(2, 0x12);
    set_program_counter(0);
    set_register_bit(REG_F, CARRY, false);

    bool result = jmp_conditional(0, &temporary_address, COND_CARRY);
    ck_assert_int_eq(temporary_address, 0x34);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(result, false);

    result = jmp_conditional(1, &temporary_address, COND_CARRY);
    ck_assert_int_eq(temporary_address, 0x1234);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, false);

    result = jmp_conditional(2, &temporary_address, COND_CARRY);
    ck_assert_int_eq(temporary_address, 0x1234);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(call_test) {
    uint16_t temporary_address = 0;

    bool result = call(0, &temporary_address);
    ck_assert_int_eq(result, true);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* branching_instruction_suite(void) {
    Suite* suite;

    suite = suite_create("Branching Instruction");

    char* test_names[TEST_CASE_SIZE] = {
        "JMP",
        "JMP_CONDITIONAL True",
        "JMP_CONDITIONAL True",
        "CALL"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        jmp_test,
        jmp_conditional_true,
        jmp_conditional_false,
        call_test
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