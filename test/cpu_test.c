#include <check.h>
#include "../src/cpu.h"
#include "../src/memory/memory_controller.h"
#include "../src/register/register_controller.h"

interceptBDOSCall(char* output) {
    size_t output_size = strlen(output);
    // Stolen from
    // https://github.com/GunshipPenguin/lib8080/blob/master/test/integration/cpmloader.c
    if (get_register(REG_C) == 2) {
        if (get_register(REG_E) != 0) {
            char ch[2];
            ch[0] = get_register(REG_E);
            ch[1] = '\0';
            strncat(output, ch, 1);
        }
    }
    else if (get_register(REG_C) == 9) {
        uint16_t addr = get_register_pair(PAIR_D);

        while (read(addr) != '$') {
            if (read(addr) != 0 && read(addr) >= 32 && read(addr) <= 126) {
                char ch[2];
                ch[0] = read(addr);
                ch[1] = '\0';
                strncat(output, ch, 1);
            }
            addr++;
        }
    }
}

START_TEST(read_file_and_load) {
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/test_file", 0);
    ck_assert_int_eq(read(0), 1);
    ck_assert_int_eq(read(1), 2);
    ck_assert_int_eq(read(2), 3);
    ck_assert_int_eq(read(3), 4);
    ck_assert_int_eq(read(4), 5);
    ck_assert_int_eq(read(5), 0);
}
END_TEST

START_TEST(diagnostic_test_1) {
    char* output = malloc(100);
    output[0] = '\0';
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/TST8080.COM", 0x100);
    write(5, 0xC9);
    set_program_counter(0xFF);

    for (int i = 0; i < 1310; i++) {
        run(1);

        if (get_program_counter() == 0) {
            break;
        }
        if (get_program_counter() == 5) {
            interceptBDOSCall(output);
        }
    }

    ck_assert_str_eq(output, "MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC VERSION 1.0  (C) 1980 CPU IS OPERATIONAL");
    free(output);
}
END_TEST

START_TEST(diagnostic_test_2) {
    char* output = malloc(100);
    output[0] = '\0';
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/8080PRE.COM", 0x100);
    write(5, 0xC9);
    set_program_counter(0xFF);

    for (int i = 0; i < 1310; i++) {
        run(1);

        if (get_program_counter() == 0) {
            break;
        }
        if (get_program_counter() == 5) {
            interceptBDOSCall(output);
        }
    }

    ck_assert_str_eq(output, "8080 Preliminary tests complete");
    free(output);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* cpu_suite(void) {
    Suite* suite;

    suite = suite_create("CPU");

    char* test_names[TEST_CASE_SIZE] = {
        "Read file and load",
        "Diagnostic Test Microcosm Associates",
        "Diagnostic Test Preliminary Z80 tests"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        read_file_and_load,
        diagnostic_test_1,
        diagnostic_test_2
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