#include "memory/memory_controller.h"
#include "unity.h"
#include <stdlib.h>

void test_read_from_address_and_return_zero() { TEST_ASSERT_EQUAL_INT(0, read_from_memory(1)); }

void test_write_a_value_to_memory() {
    write_to_memory(1, 10);
    TEST_ASSERT_EQUAL_INT(10, read_from_memory(1));
}

void test_load_memory_test() {
    uint8_t *file_data = malloc(2);
    file_data[0] = 0x10;
    file_data[1] = 0x55;

    load_memory(file_data, 2, 0);
    TEST_ASSERT_EQUAL_INT(0x10, read_from_memory(0));
    TEST_ASSERT_EQUAL_INT(0x55, read_from_memory(1));
    TEST_ASSERT_EQUAL_INT(0, read_from_memory(2));

    free(file_data);
}

void run_memory_controller_test() {
    printf("Memory controller:\n");
    RUN_TEST(test_read_from_address_and_return_zero);
    RUN_TEST(test_write_a_value_to_memory);
    RUN_TEST(test_load_memory_test);
}