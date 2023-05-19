#include <check.h>
#include <stdlib.h>

Suite* memory_controller_suite(void);
Suite* logical_instruction_suite(void);
Suite* instruction_suite(void);
Suite* register_controller_suite(void);
Suite* arithmetic_instruction_suite(void);

int main(void) {
    int number_failed;
    SRunner* test_runner;

    // Include the suites
    test_runner = srunner_create(memory_controller_suite());
    srunner_add_suite(test_runner, logical_instruction_suite());
    srunner_add_suite(test_runner, instruction_suite());
    srunner_add_suite(test_runner, register_controller_suite());
    srunner_add_suite(test_runner, arithmetic_instruction_suite());

    // Run tests
    srunner_run_all(test_runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(test_runner);
    srunner_free(test_runner);

    return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
