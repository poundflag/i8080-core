#include <check.h>
#include "../../src/instruction/instruction.h"
#include "../../src/register/register_controller.h"

START_TEST(getDestinationRegister_returns_the_valid_index) {
    ck_assert_int_eq(get_destination_register(0x00), REG_B);
    ck_assert_int_eq(get_destination_register(0x07), REG_B);
    ck_assert_int_eq(get_destination_register(0x08), REG_C);
    ck_assert_int_eq(get_destination_register(0x0F), REG_C);

    ck_assert_int_eq(get_destination_register(0x40), REG_B);
    ck_assert_int_eq(get_destination_register(0x47), REG_B);
    ck_assert_int_eq(get_destination_register(0x48), REG_C);
    ck_assert_int_eq(get_destination_register(0x4F), REG_C);

    ck_assert_int_eq(get_destination_register(0x50), REG_D);
    ck_assert_int_eq(get_destination_register(0x57), REG_D);
    ck_assert_int_eq(get_destination_register(0x58), REG_E);
    ck_assert_int_eq(get_destination_register(0x5F), REG_E);

    ck_assert_int_eq(get_destination_register(0x60), REG_H);
    ck_assert_int_eq(get_destination_register(0x67), REG_H);
    ck_assert_int_eq(get_destination_register(0x68), REG_L);
    ck_assert_int_eq(get_destination_register(0x6F), REG_L);

    ck_assert_int_eq(get_destination_register(0x70), REG_M);
    ck_assert_int_eq(get_destination_register(0x77), REG_M);
    ck_assert_int_eq(get_destination_register(0x78), REG_A);
    ck_assert_int_eq(get_destination_register(0x7F), REG_A);
}
END_TEST

START_TEST(getSourceRegister_returns_the_valid_index) {
    ck_assert_int_eq(get_source_register(0x40), REG_B);
    ck_assert_int_eq(get_source_register(0x41), REG_C);
    ck_assert_int_eq(get_source_register(0x42), REG_D);
    ck_assert_int_eq(get_source_register(0x43), REG_E);
    ck_assert_int_eq(get_source_register(0x44), REG_H);
    ck_assert_int_eq(get_source_register(0x45), REG_L);
    ck_assert_int_eq(get_source_register(0x46), REG_M);
    ck_assert_int_eq(get_source_register(0x47), REG_A);

    ck_assert_int_eq(get_source_register(0x48), REG_B);
    ck_assert_int_eq(get_source_register(0x49), REG_C);
    ck_assert_int_eq(get_source_register(0x4A), REG_D);
    ck_assert_int_eq(get_source_register(0x4B), REG_E);
    ck_assert_int_eq(get_source_register(0x4C), REG_H);
    ck_assert_int_eq(get_source_register(0x4D), REG_L);
    ck_assert_int_eq(get_source_register(0x4E), REG_M);
    ck_assert_int_eq(get_source_register(0x4F), REG_A);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* instruction_suite(void) {
    Suite* suite;

    suite = suite_create("Instruction");

    char* test_names[TEST_CASE_SIZE] = {
        "get_destination_register returns the valid index",
        "get_source_register returns the valid index"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        getDestinationRegister_returns_the_valid_index,
        getSourceRegister_returns_the_valid_index

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