#include <check.h>
#include "../../src/instruction/logical_instruction.h"
#include "../../src/instruction/instruction.h"
#include "../../src/register/register_controller.h"
#include "../../src/memory/memory_controller.h"

START_TEST(mov_value) {
    uint8_t source = 10;
    uint8_t destination = 0;
    mov(&destination, source);

    ck_assert_int_eq(destination, source);
    ck_assert_int_eq(destination, 10);
}
END_TEST

START_TEST(mvi_value) {
    uint8_t destination = 0;
    machine_cycle = 0;
    set_program_counter(0);
    write(1, 50);

    mvi(&destination);
    ck_assert_int_eq(get_program_counter(), 1);
    machine_cycle++;

    mvi(&destination);
    ck_assert_int_eq(destination, 50);
    ck_assert_int_eq(destination, read(1));
    machine_cycle++;

    mvi(&destination);
    ck_assert_int_eq(get_program_counter(), 2);
    ck_assert_int_eq(machine_cycle, 0);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* logical_instruction_suite(void) {
    Suite* suite;

    suite = suite_create("Logical Instruction");

    char* test_names[TEST_CASE_SIZE] = {
        "MOV Value",
        "MVI Value"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        mov_value,
        mvi_value
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