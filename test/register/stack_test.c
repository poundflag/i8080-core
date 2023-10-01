#include "memory/memory_controller.h"
#include "register/stack.h"
#include "unity.h"

void test_get_the_default_stack_pointer_address() { TEST_ASSERT_EQUAL_INT(get_stack_pointer(), 0); }

void test_set_stack_pointer_test() {
    set_stack_pointer(0x1234);
    TEST_ASSERT_EQUAL_INT(0x1234, get_stack_pointer());
}

void test_push_word_test() {
    set_stack_pointer(2);
    push_word(0x1234);

    TEST_ASSERT_EQUAL_INT(0x34, read_from_memory(0));
    TEST_ASSERT_EQUAL_INT(0x12, read_from_memory(1));
    TEST_ASSERT_EQUAL_INT(0, get_stack_pointer());
    TEST_ASSERT_EQUAL_INT(0x1234, pull_word());
    TEST_ASSERT_EQUAL_INT(2, get_stack_pointer());
}

void run_stack_test() {
    printf("Stack test:\n");
    RUN_TEST(test_get_the_default_stack_pointer_address);
    RUN_TEST(test_set_stack_pointer_test);
    RUN_TEST(test_push_word_test);
}