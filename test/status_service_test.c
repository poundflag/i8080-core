#include <check.h>
#include "../src/instruction/logical_instruction.h"
#include "../src/status_service.h"
#include "../src/cpu.h"
#include "../src/memory/memory_controller.h"

START_TEST(be_true_when_stack_is_accessed) {
    uint16_t temporary_address = 0;
    ck_assert_int_eq(is_stack_access(), false);

    push(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(is_stack_access(), true);
    push(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(is_stack_access(), true);
    push(PAIR_B, 2, &temporary_address);
    ck_assert_int_eq(is_stack_access(), false);

    pop(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(is_stack_access(), true);
    pop(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(is_stack_access(), true);
    pop(PAIR_B, 2, &temporary_address);
    ck_assert_int_eq(is_stack_access(), false);
}
END_TEST

START_TEST(be_false_when_memory_is_not_read) {
    uint16_t temporary_address = 0;
    ck_assert_int_eq(is_memory_read(), true);

    sta(0, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);
    sta(1, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);
    sta(2, &temporary_address);
    ck_assert_int_eq(is_memory_read(), false);
    sta(3, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);

    shld(0, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);
    shld(1, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);
    shld(2, &temporary_address);
    ck_assert_int_eq(is_memory_read(), false);
    shld(3, &temporary_address);
    ck_assert_int_eq(is_memory_read(), false);
    shld(4, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);

    stax(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(is_memory_read(), false);
    stax(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);

    push(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(is_memory_read(), false);
    push(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(is_memory_read(), false);
    push(PAIR_B, 2, &temporary_address);
    ck_assert_int_eq(is_memory_read(), true);
}
END_TEST

START_TEST(be_true_when_first_machine_cycle) {
    uint16_t temporary_address = 0;
    int machine_cycle = 0;
    write(0, 0xC6);
    ck_assert_int_eq(is_first_machine_cycle(), true);

    step(&machine_cycle, &temporary_address); // Read opcode
    ck_assert_int_eq(is_first_machine_cycle(), false);
    step(&machine_cycle, &temporary_address); // Execute with immediate value in addr. 1
    ck_assert_int_eq(is_first_machine_cycle(), true);
}
END_TEST

START_TEST(be_false_when_write_output) {
    uint16_t temporary_address = 0;
    ck_assert_int_eq(is_write_output(), true);

    sta(0, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);
    sta(1, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);
    sta(2, &temporary_address);
    ck_assert_int_eq(is_write_output(), false);
    sta(3, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);

    shld(0, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);
    shld(1, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);
    shld(2, &temporary_address);
    ck_assert_int_eq(is_write_output(), false);
    shld(3, &temporary_address);
    ck_assert_int_eq(is_write_output(), false);
    shld(4, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);

    stax(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(is_write_output(), false);
    stax(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);

    push(PAIR_B, 0, &temporary_address);
    ck_assert_int_eq(is_write_output(), false);
    push(PAIR_B, 1, &temporary_address);
    ck_assert_int_eq(is_write_output(), false);
    push(PAIR_B, 2, &temporary_address);
    ck_assert_int_eq(is_write_output(), true);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* status_service_suite(void) {
    Suite* suite;

    suite = suite_create("Status Service");

    char* test_names[TEST_CASE_SIZE] = {
        "Be true when stack is accessed",
        "Be false when memory is not read",
        "Be true when first machine cycle",
        "Be false when write output"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        be_true_when_stack_is_accessed,
        be_false_when_memory_is_not_read,
        be_true_when_first_machine_cycle,
        be_false_when_write_output
    };

    for (int i = 0; i < TEST_CASE_SIZE; i++) {
        // Create a new test case for each iteration
        TCase* test_case = tcase_create(test_names[i]);
        tcase_set_timeout(test_case, 0);

        // Add the corresponding test function based on the index
        tcase_add_test(test_case, test_functions[i]);

        // Add the test case to the suite
        suite_add_tcase(suite, test_case);
    }

    return suite;
}