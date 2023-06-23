#include "unity.h"
#include <stdio.h>
#include "../src/utils.h"

void test_return_error_on_invalid_args() {
    // Redirect stdout to a string
    char output[100];
    FILE* temp_stdout = fmemopen(output, sizeof(output), "w");
    setbuf(temp_stdout, NULL);
    FILE* original_stdout = stdout;
    stdout = temp_stdout;

    // Simulate command line arguments
    char* testArgs[] = { "program", "arg1", "arg2" };
    int testArgc = sizeof(testArgs) / sizeof(testArgs[0]);

    // Call the process_arguments function
    process_arguments(testArgc, testArgs);

    // Close the redirected stdout
    fclose(temp_stdout);
    stdout = original_stdout;

    // Compare the output with the expected value
    TEST_ASSERT_EQUAL_STRING("arg1 is an invalid command\narg2 is an invalid command\n", output);
}

void test_process_file_input() {
    // Redirect stdout to a string
    char output[100];
    FILE* temp_stdout = fmemopen(output, sizeof(output), "w");
    setbuf(temp_stdout, NULL);
    FILE* original_stdout = stdout;
    stdout = temp_stdout;

    // Simulate command line arguments
    char* testArgs[] = { "program", "-i", "/home/robin/Dokumente/Projects/i8080-core/rom/8080EXER.COM" };
    int testArgc = sizeof(testArgs) / sizeof(testArgs[0]);

    // Call the process_arguments function
    process_arguments(testArgc, testArgs);

    // Close the redirected stdout
    fclose(temp_stdout);
    stdout = original_stdout;

    // Compare the output with the expected value
    TEST_ASSERT_EQUAL_STRING(output, "Loading file: /home/robin/Dokumente/Projects/i8080-core/rom/8080EXER.COM\n");
}

void test_process_file_output() {
    // Redirect stdout to a string
    char output[100];
    FILE* temp_stdout = fmemopen(output, sizeof(output), "w");
    setbuf(temp_stdout, NULL);
    FILE* original_stdout = stdout;
    stdout = temp_stdout;

    // Simulate command line arguments
    char* testArgs[] = { "program", "-o", "Hello.txt" };
    int testArgc = sizeof(testArgs) / sizeof(testArgs[0]);

    // Call the process_arguments function
    process_arguments(testArgc, testArgs);

    // Close the redirected stdout
    fclose(temp_stdout);
    stdout = original_stdout;

    // Removing the test file
    remove("Hello.txt");

    // Compare the output with the expected value
    TEST_ASSERT_EQUAL_STRING(output, "Set Output file: Hello.txt\n");
}

void test_step_the_cpu_finite() {
    // Redirect stdout to a string
    char output[100];
    FILE* temp_stdout = fmemopen(output, sizeof(output), "w");
    setbuf(temp_stdout, NULL);
    FILE* original_stdout = stdout;
    stdout = temp_stdout;

    // Simulate command line arguments
    char* testArgs[] = { "program", "-steps", "10" };
    int testArgc = sizeof(testArgs) / sizeof(testArgs[0]);

    // Call the process_arguments function
    process_arguments(testArgc, testArgs);

    // Close the redirected stdout
    fclose(temp_stdout);
    stdout = original_stdout;

    // Compare the output with the expected value
    TEST_ASSERT_EQUAL_STRING(output, "Running cpu for 10 steps\n");
    TEST_ASSERT_EQUAL_INT(current_running_mode, STEPPING);
    TEST_ASSERT_EQUAL_INT(steps_to_run, 10);
}

void test_step_the_cpu_infinite() {
    // Redirect stdout to a string
    char output[100];
    FILE* temp_stdout = fmemopen(output, sizeof(output), "w");
    setbuf(temp_stdout, NULL);
    FILE* original_stdout = stdout;
    stdout = temp_stdout;

    // Simulate command line arguments
    char* testArgs[] = { "program", "-steps", "-1" };
    int testArgc = sizeof(testArgs) / sizeof(testArgs[0]);

    // Call the process_arguments function
    process_arguments(testArgc, testArgs);

    // Close the redirected stdout
    fclose(temp_stdout);
    stdout = original_stdout;

    // Compare the output with the expected value
    TEST_ASSERT_EQUAL_STRING(output, "Running cpu infinite\n");
    TEST_ASSERT_EQUAL_INT(current_running_mode, INDEFINITE);
    TEST_ASSERT_EQUAL_INT(steps_to_run, -1);
}

void run_utils_test() {
    printf("Utils:\n");
    RUN_TEST(test_return_error_on_invalid_args);
    RUN_TEST(test_process_file_input);
    RUN_TEST(test_process_file_output);
    RUN_TEST(test_step_the_cpu_finite);
    RUN_TEST(test_step_the_cpu_infinite);
}