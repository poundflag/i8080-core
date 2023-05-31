#include <check.h>
#include "../src/cpu.h"
#include "../src/memory/memory_controller.h"
#include "../src/register/register_controller.h"

START_TEST(read_file_and_load) {
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/test_file");
    ck_assert_int_eq(read(0), 1);
    ck_assert_int_eq(read(1), 2);
    ck_assert_int_eq(read(2), 3);
    ck_assert_int_eq(read(3), 4);
    ck_assert_int_eq(read(4), 5);
    ck_assert_int_eq(read(5), 0);
}
END_TEST

START_TEST(diagnostic_test_1) {
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/test_file");
    write(5, 0xC9);
    set_program_counter(0x100);

    ck_assert_int_eq(read(0), 0);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* cpu_suite(void) {
    Suite* suite;

    suite = suite_create("CPU");

    char* test_names[TEST_CASE_SIZE] = {
        "Read file and load",
        "Diagnostic Test Microcosm Associates"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        read_file_and_load,
        diagnostic_test_1
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