#include "../include/utils/file_io.h"
#include "unity.h"

void read_a_file() {
    File_Response file_response = read_binary_from_file("rom/test_file");

    TEST_ASSERT_EQUAL_INT(1, *file_response.file_data);
    TEST_ASSERT_EQUAL_INT(2, *file_response.file_data + 1);
    TEST_ASSERT_EQUAL_INT(3, *file_response.file_data + 2);
    TEST_ASSERT_EQUAL_INT(4, *file_response.file_data + 3);
    TEST_ASSERT_EQUAL_INT(5, *file_response.file_data + 4);
    TEST_ASSERT_EQUAL_INT(5, file_response.file_size);

    free(file_response.file_data);
}

void read_a_file_that_doesnt_exist() {
    File_Response file_response = read_binary_from_file("rom/doesnt_exist_file");

    TEST_ASSERT_EQUAL_size_t(-1, file_response.file_size);
    TEST_ASSERT_NULL(file_response.file_data);
}

void write_a_string_to_a_file() {
    bool write_success = write_string_to_file("HELLO", "hello_test.txt");
    File_Response file_response = read_binary_from_file("hello_test.txt");

    TEST_ASSERT_TRUE(write_success);
    TEST_ASSERT_EQUAL_CHAR(0x48, *file_response.file_data);
    TEST_ASSERT_EQUAL_CHAR(0x49, *file_response.file_data + 1);
    TEST_ASSERT_EQUAL_CHAR(0x4A, *file_response.file_data + 2);
    TEST_ASSERT_EQUAL_CHAR(0x4B, *file_response.file_data + 3);
    TEST_ASSERT_EQUAL_CHAR(0x4C, *file_response.file_data + 4);
    TEST_ASSERT_EQUAL_INT(5, file_response.file_size);

    free(file_response.file_data);
    remove_file("hello_test.txt");
}

void write_a_string_to_an_invalid_file_path() {
    bool write_failure = write_string_to_file("HELLO", "/no_exist/test.txt");
    TEST_ASSERT_FALSE(write_failure);
}

void remove_a_file() {
    write_string_to_file("HELLO", "hello_test.txt");
    bool remove_success = remove_file("hello_test.txt");
    TEST_ASSERT_TRUE(remove_success);
}

void remove_a_file_that_doesnt_exist() {
    bool remove_failure = remove_file("test123.txt");
    TEST_ASSERT_FALSE(remove_failure);
}

void run_file_io_test() {
    printf("File IO:\n");
    RUN_TEST(read_a_file);
    RUN_TEST(read_a_file_that_doesnt_exist);
    RUN_TEST(write_a_string_to_a_file);
    RUN_TEST(write_a_string_to_an_invalid_file_path);
    RUN_TEST(remove_a_file);
    RUN_TEST(remove_a_file_that_doesnt_exist);
}