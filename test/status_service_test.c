#include <check.h>
#include "../src/instruction/logical_instruction.h"
#include "../src/status_service.h"

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

/* FOR MEMR
sta
shld
stax
push
xthl
*/

#define TEST_CASE_SIZE 100

Suite* status_service_suite(void) {
    Suite* suite;

    suite = suite_create("Status Service");

    char* test_names[TEST_CASE_SIZE] = {
        "Be true when stack is accessed"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        be_true_when_stack_is_accessed
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