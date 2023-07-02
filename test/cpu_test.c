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

        while (read(addr) != '$') {
            if (read(addr) != 0 && read(addr) >= 32 && read(addr) <= 126) {
                // printf("%c", read(addr));
                char ch[2];
                ch[0] = read(addr);
                ch[1] = '\0';
                strncat(output, ch, 1);
            }
            addr++;
        }
    }
}

void test_read_file_and_load() {
    load_file("rom/test_file", 0);
    TEST_ASSERT_EQUAL_INT(read(0), 1);
    TEST_ASSERT_EQUAL_INT(read(1), 2);
    TEST_ASSERT_EQUAL_INT(read(2), 3);
    TEST_ASSERT_EQUAL_INT(read(3), 4);
    TEST_ASSERT_EQUAL_INT(read(4), 5);
    TEST_ASSERT_EQUAL_INT(read(5), 0);
}

void test_diagnostic_test_1() {
    char *output = malloc(100);
    output[0] = '\0';
    load_file("rom/TST8080.COM", 0x100);
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

    TEST_ASSERT_EQUAL_STRING("MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC "
                             "VERSION 1.0  (C) 1980 CPU IS OPERATIONAL",
                             output);
    free(output);
}

void test_diagnostic_test_2() {
    char *output = malloc(100);
    output[0] = '\0';
    load_file("rom/8080PRE.COM", 0x100);
    write(5, 0xC9);
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
    write(5, 0xC9);
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
    write(5, 0xC9);
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
    RUN_TEST(test_diagnostic_test_1);
    RUN_TEST(test_diagnostic_test_2);
    RUN_TEST(test_diagnostic_test_3);
    RUN_TEST(test_diagnostic_test_4);
}