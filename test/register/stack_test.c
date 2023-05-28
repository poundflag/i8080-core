#include <check.h>
#include "../../src/register/stack.h"
#include "../../src/memory/memory_controller.h"

START_TEST(get_the_default_stack_pointer_address) {
    ck_assert_int_eq(get_stack_pointer(), 0);
}
END_TEST

START_TEST(set_stack_pointer_test) {
    set_stack_pointer(0x1234);
    ck_assert_int_eq(get_stack_pointer(), 0x1234);
}
END_TEST

START_TEST(push_word_test) {
    set_stack_pointer(2);
    push_word(0x1234);

    ck_assert_int_eq(read(0), 0x34);
    ck_assert_int_eq(read(1), 0x12);
    ck_assert_int_eq(get_stack_pointer(), 0);
    ck_assert_int_eq(pull_word(), 0x1234);
    ck_assert_int_eq(get_stack_pointer(), 2);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* stack_suite(void) {
    Suite* suite;

    suite = suite_create("Stack");

    char* test_names[TEST_CASE_SIZE] = {
        "Get the default stack pointer address",
        "Set Stack Pointer",
        "Push Word"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        get_the_default_stack_pointer_address,
        set_stack_pointer_test,
        push_word_test
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