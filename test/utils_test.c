#include <check.h>
#include <stdio.h>
#include "../src/utils.h"

START_TEST(return_error_on_invalid_args) {
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
    ck_assert_str_eq(output, "arg1 is an invalid command\narg2 is an invalid command\n");
}
END_TEST

START_TEST(process_file_input) {
    // Redirect stdout to a string
    char output[100];
    FILE* temp_stdout = fmemopen(output, sizeof(output), "w");
    setbuf(temp_stdout, NULL);
    FILE* original_stdout = stdout;
    stdout = temp_stdout;

    // Simulate command line arguments
    char* testArgs[] = { "program", "-i", "Hello.txt" };
    int testArgc = sizeof(testArgs) / sizeof(testArgs[0]);

    // Call the process_arguments function
    process_arguments(testArgc, testArgs);

    // Close the redirected stdout
    fclose(temp_stdout);
    stdout = original_stdout;

    // Compare the output with the expected value
    ck_assert_str_eq(output, "Loaded file: Hello.txt\n");
}
END_TEST

START_TEST(process_file_output) {
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

    // Compare the output with the expected value
    ck_assert_str_eq(output, "Set Output file: Hello.txt\n");
}
END_TEST

START_TEST(step_the_cpu_finite) {
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
    ck_assert_str_eq(output, "Running cpu for 10 steps\n");
}
END_TEST

START_TEST(step_the_cpu_infinite) {
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
    ck_assert_str_eq(output, "Running cpu infinite\n");
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* utils_suite(void) {
    Suite* suite;

    suite = suite_create("UTILS");

    char* test_names[TEST_CASE_SIZE] = {
        "Return error on invalid args",
        "Process file input",
        "Process file output",
        "Step the cpu finite",
        "Step the cpu infinite"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        return_error_on_invalid_args,
        process_file_input,
        process_file_output,
        step_the_cpu_finite,
        step_the_cpu_infinite
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