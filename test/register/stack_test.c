#include "memory/memory_controller.h"
#include "register/stack.h"
#include "unity.h"

void test_get_the_default_stack_pointer_address() { TEST_ASSERT_EQUAL_INT(get_stack_pointer(), 0); }

void test_set_stack_pointer_test() {
    set_stack_pointer(0x1234);
    TEST_ASSERT_EQUAL_INT(get_stack_pointer(), 0x1234);
}

void test_push_word_test() {
    set_stack_pointer(2);
    push_word(0x1234);

    TEST_ASSERT_EQUAL_INT(read_from_memory(0), 0x34);
    TEST_ASSERT_EQUAL_INT(read_from_memory(1), 0x12);
    TEST_ASSERT_EQUAL_INT(get_stack_pointer(), 0);
    TEST_ASSERT_EQUAL_INT(pull_word(), 0x1234);
    TEST_ASSERT_EQUAL_INT(get_stack_pointer(), 2);
}

void run_stack_test() {
    printf("Stack test:\n");
    RUN_TEST(test_get_the_default_stack_pointer_address);
    RUN_TEST(test_set_stack_pointer_test);
    RUN_TEST(test_push_word_test);
}