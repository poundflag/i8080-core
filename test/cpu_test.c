#include "cpu.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "unity.h"
#include <string.h>

void interceptBDOSCall(char *output) {
    size_t output_size = strlen(output);
    // Stolen from
    // https://github.com/GunshipPenguin/lib8080/blob/master/test/integration/cpmloader.c
    if (get_register(REG_C) == 2) {
        if (get_register(REG_E) != 0 && get_register(REG_E) >= 32 && get_register(REG_E) <= 126) {
            // printf("%c", get_register(REG_E));
            char ch[2];
            ch[0] = get_register(REG_E);
            ch[1] = '\0';
            strncat(output, ch, 1);
        }
    } else if (get_register(REG_C) == 9) {
        uint16_t addr = get_register_pair(PAIR_D);

        while (read_from_memory(addr) != '$') {
            if (read_from_memory(addr) != 0 && read_from_memory(addr) >= 32 && read_from_memory(addr) <= 126) {
                // printf("%c", read_from_memory(addr));
                char ch[2];
                ch[0] = read_from_memory(addr);
                ch[1] = '\0';
                strncat(output, ch, 1);
            }
            addr++;
        }
    }
}

void test_read_file_and_load() {
    load_file("rom/test_file", 0);
    TEST_ASSERT_EQUAL_INT(1, read_from_memory(0));
    TEST_ASSERT_EQUAL_INT(2, read_from_memory(1));
    TEST_ASSERT_EQUAL_INT(3, read_from_memory(2));
    TEST_ASSERT_EQUAL_INT(4, read_from_memory(3));
    TEST_ASSERT_EQUAL_INT(5, read_from_memory(4));
    TEST_ASSERT_EQUAL_INT(0, read_from_memory(5));
}

void check_if_the_system_successfully_halts() {
    write_to_memory(1, 0x76);
    run(2);
    TEST_ASSERT_TRUE(has_system_halted());
}

void test_diagnostic_test_1() {
    char *output = malloc(100);
    output[0] = '\0';
    load_file("rom/TST8080.COM", 0x100);
    write_to_memory(5, 0xC9);
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

    TEST_ASSERT_EQUAL_STRING("MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC "
                             "VERSION 1.0  (C) 1980 CPU IS OPERATIONAL",
                             output);
    free(output);
}

void test_diagnostic_test_2() {
    char *output = malloc(100);
    output[0] = '\0';
    load_file("rom/8080PRE.COM", 0x100);
    write_to_memory(5, 0xC9);
    set_program_counter(0xFF);

    for (int i = 0; i < 2000; i++) {
        run(1);

        if (get_program_counter() == 0) {
            break;
        }
        if (get_program_counter() == 5) {
            interceptBDOSCall(output);
        }
    }

    TEST_ASSERT_EQUAL_STRING("8080 Preliminary tests complete", output);
    free(output);
}

void test_diagnostic_test_3() {
    char *output = malloc(176 * sizeof(char));
    output[0] = '\0';
    load_file("rom/CPUTEST.COM", 0x100);
    write_to_memory(5, 0xC9);
    set_program_counter(0xFF);

    while (get_program_counter() != 0) {
        run(1);

        if (get_program_counter() == 5) {
            interceptBDOSCall(output);
        }
    }

    TEST_ASSERT_EQUAL_STRING("DIAGNOSTICS II V1.2 - CPU TESTCOPYRIGHT (C) 1981 - SUPERSOFT ASSOCIATESABCDEFGHIJKLMNOPQRSTUVWXYZCPU IS 8080/8085BEGIN "
                             "TIMING TESTEND TIMING TESTCPU TESTS OK",
                             output);
    free(output);
}

void test_diagnostic_test_4() {
    char *output = malloc(891 * sizeof(char));
    output[0] = '\0';
    load_file("rom/8080EXER.COM", 0x100);
    write_to_memory(5, 0xC9);
    set_program_counter(0xFF);

    while (get_program_counter() != 0) {
        run(1);

        if (get_program_counter() == 5) {
            interceptBDOSCall(output);
        }
    }

    TEST_ASSERT_EQUAL_STRING(
        "8080 instruction exerciserdad <b,d,h,sp>................  OKaluop nn......................  OKaluop "
        "<b,c,d,e,h,l,m,a>.......  OK<daa,cma,stc,cmc>.............  OK<inr,dcr> a...................  OK<inr,dcr> b...................  OK<inx,dcx> "
        "b...................  OK<inr,dcr> c...................  OK<inr,dcr> d...................  OK<inx,dcx> d...................  OK<inr,dcr> "
        "e...................  OK<inr,dcr> h...................  OK<inx,dcx> h...................  OK<inr,dcr> l...................  OK<inr,dcr> "
        "m...................  OK<inx,dcx> sp..................  OKlhld nnnn.....................  OKshld nnnn.....................  OKlxi "
        "<b,d,h,sp>,nnnn...........  OKldax <b,d>....................  OKmvi <b,c,d,e,h,l,m,a>,nn......  OKmov <bcdehla>,<bcdehla>.......  OKsta "
        "nnnn / lda nnnn...........  OK<rlc,rrc,ral,rar>.............  OKstax <b,d>....................  OKTests complete",
        output);
    free(output);
}

void run_cpu_test() {
    printf("CPU:\n");
    RUN_TEST(test_read_file_and_load);
    RUN_TEST(check_if_the_system_successfully_halts);
    RUN_TEST(test_diagnostic_test_1);
    RUN_TEST(test_diagnostic_test_2);
    RUN_TEST(test_diagnostic_test_3);
    RUN_TEST(test_diagnostic_test_4);
}