#include <check.h>
#include "../src/cpu.h"
#include "../src/memory/memory_controller.h"
#include "../src/register/register_controller.h"

interceptBDOSCall() {
    // Stolen from
    // https://github.com/GunshipPenguin/lib8080/blob/master/test/integration/cpmloader.c
    printf("HELLO");
    if (get_register(REG_C) == 2) {
        if (get_register(REG_E) != 0) {
            printf((char)get_register(REG_E));
            //*output += (char)get_register(REG_E);
        }
    }
    else if (get_register(REG_C) == 9) {
        for (int addr = get_register(REG_D); read(addr) != '$'; addr++) {
            if (read(addr) != 0) {
                printf((char)read(addr));
                //*output += read(addr);
            }
        }
    }
}

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
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/TST8080.COM");
    write(5, 0xC9);
    set_program_counter(0xFF);

    for (int i = 0; i < 1310; i++) { // 67d
        run(1);

        if (get_program_counter() == 0) {
            break;
        }
        if (get_program_counter() == 5) {
            //printf("\nHELLO\n");
            /*if (get_register(REG_C) == 2) {
                if (get_register(REG_E) != 0) {
                    // printf("%c", (char)get_register(REG_E));
                    //*output += (char)get_register(REG_E);
                }
            }
            else */if (get_register(REG_C) == 9) {
                uint16_t addr = get_register(REG_H);

                while (read(addr) != '$') {
                    if (read(addr) != 0) {
                        printf(" %c ", read(addr));
                    }
                    addr++;
                }
            }
        }
    }

    ck_assert_int_eq(0, "MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC\r\n VERSION 1.0  (C) "
        "1980\r\n\r\n CPU IS OPERATIONAL");
    // free(output);
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