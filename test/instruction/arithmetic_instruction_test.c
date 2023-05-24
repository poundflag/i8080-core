#include <check.h>
#include <stdbool.h>
#include "../../src/instruction/arithmetic_instruction.h"
#include "../../src/register/register_controller.h"
#include "../../src/memory/memory_controller.h"

START_TEST(add_test) {
    set_register(REG_A, 0x12);
    set_register(REG_B, 0x12);

    bool result = add(REG_B);
    ck_assert_int_eq(get_register(REG_A), 0x24);
    ck_assert_int_eq(get_register(REG_F), 0b00000110);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(add_overflow) {
    set_register(REG_A, 0xFF);
    set_register(REG_B, 0x10);

    bool result = add(REG_B);
    ck_assert_int_eq(get_register(REG_A), 0xF);
    ck_assert_int_eq(get_register(REG_F), 0b00000111);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(adi_test) {
    set_program_counter(0);
    write(1, 0x12);
    set_register(REG_A, 0x12);

    bool result = adi(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = adi(1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0x24);
    ck_assert_int_eq(get_register(REG_F), 0b00000110);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(adi_overflow) {
    set_program_counter(0);
    write(1, 0xFF);
    set_register(REG_A, 0x10);

    bool result = adi(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = adi(1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0xF);
    ck_assert_int_eq(get_register(REG_F), 0b00000111);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(adc_no_carry) {
    set_register(REG_A, 1);
    set_register(REG_B, 1);

    bool result = adc(REG_B, false);
    ck_assert_int_eq(get_register(REG_A), 0x2);
    ck_assert_int_eq(get_register(REG_F), 0b00000010);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(adc_carry) {
    set_register(REG_A, 1);
    set_register(REG_B, 1);

    bool result = adc(REG_B, true);
    ck_assert_int_eq(get_register(REG_A), 0x3);
    ck_assert_int_eq(get_register(REG_F), 0b00000110);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(aci_no_carry) {
    set_program_counter(0);
    write(1, 1);
    set_register(REG_A, 1);

    bool result = aci(false, 0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = aci(false, 1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0x2);
    ck_assert_int_eq(get_register(REG_F), 0b00000010);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(aci_carry) {
    set_program_counter(0);
    write(1, 1);
    set_register(REG_A, 1);

    bool result = aci(true, 0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = aci(true, 1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0x3);
    ck_assert_int_eq(get_register(REG_F), 0b00000110);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sub_test) {
    set_register(REG_A, 5);
    set_register(REG_B, 1);

    bool result = sub(REG_B);
    ck_assert_int_eq(get_register(REG_A), 4);
    ck_assert_int_eq(get_register(REG_F), 0b00010010);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sub_overflow) {
    set_register(REG_A, 1);
    set_register(REG_B, 5);

    bool result = sub(REG_B);
    ck_assert_int_eq(get_register(REG_A), 0xFC);
    ck_assert_int_eq(get_register(REG_F), 0b10000111);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sui_test) {
    set_program_counter(0);
    write(1, 1);
    set_register(REG_A, 5);

    bool result = sui(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = sui(1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 4);
    ck_assert_int_eq(get_register(REG_F), 0b00010010);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sui_overflow) {
    set_program_counter(0);
    write(1, 5);
    set_register(REG_A, 1);

    bool result = sui(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = sui(1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0xFC);
    ck_assert_int_eq(get_register(REG_F), 0b10000111);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sbb_no_carry) {
    set_register(REG_A, 5);
    set_register(REG_B, 1);

    bool result = sbb(REG_B, false);
    ck_assert_int_eq(get_register(REG_A), 0x4);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sbb_carry) {
    set_register(REG_A, 5);
    set_register(REG_B, 1);

    bool result = sbb(REG_B, true);
    ck_assert_int_eq(get_register(REG_A), 0x3);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sbi_no_carry) {
    set_program_counter(0);
    write(1, 1);
    set_register(REG_A, 5);

    bool result = sbi(false, 0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = sbi(false, 1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0x4);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(sbi_carry) {
    set_program_counter(0);
    write(1, 1);
    set_register(REG_A, 5);

    bool result = sbi(true, 0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = sbi(true, 1);
    ck_assert_int_eq(get_program_counter(), 1);
    ck_assert_int_eq(get_register(REG_A), 0x3);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(inr_test) {
    set_register(REG_B, 1);

    bool result = inr(REG_B);
    ck_assert_int_eq(get_register(REG_B), 2);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(inr_overflow) {
    set_register(REG_B, 0xFF);

    bool result = inr(REG_B);
    ck_assert_int_eq(get_register(REG_B), 0);
    ck_assert_int_eq(get_register(REG_F), 0b01010110);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(dcr_test) {
    set_register(REG_B, 1);

    bool result = dcr(REG_B);
    ck_assert_int_eq(get_register(REG_B), 0);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(dcr_test_1) {
    set_register(REG_B, 2);

    bool result = dcr(REG_B);
    ck_assert_int_eq(get_register(REG_B), 1);
    ck_assert_int_eq(((get_register(REG_F) >> 4) & 1), 1);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(dcr_overflow) {
    set_register(REG_B, 0);

    bool result = dcr(REG_B);
    ck_assert_int_eq(get_register(REG_B), 0xFF);
    ck_assert_int_eq(get_register(REG_F), 0b10000110);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(inx_test) {
    set_register_pair(PAIR_B, 0x44);

    bool result = inx(PAIR_B);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0x45);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(dcx_test) {
    set_register_pair(PAIR_B, 0x44);

    bool result = dcx(PAIR_B);
    ck_assert_int_eq(get_register_pair(PAIR_B), 0x43);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(dad_test) {
    set_register_pair(PAIR_B, 0x1234);
    set_register_pair(PAIR_H, 0x1234);

    bool result = dad(PAIR_B);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0x2468);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(dad_overflow) {
    set_register_pair(PAIR_B, 0x4444);
    set_register_pair(PAIR_H, 0xFFFF);

    bool result = dad(PAIR_B);
    ck_assert_int_eq(get_register_pair(PAIR_H), 0x4443);
    ck_assert_int_eq((get_register(REG_F) & 1), 1);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(daa_test) {
    bool result = daa();
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(ana_test) {
    set_register(REG_A, 4);
    set_register(REG_B, 6);

    bool result = ana(REG_B);
    ck_assert_int_eq(get_register(REG_A), 4);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(ani_test) {
    set_register(REG_A, 4);
    write(1, 6);

    bool result = ani(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = ani(1);
    ck_assert_int_eq(get_register(REG_A), 4);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(ora_test) {
    set_register(REG_A, 1);
    set_register(REG_B, 2);

    bool result = ora(REG_B);
    ck_assert_int_eq(get_register(REG_A), 3);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(ori_test) {
    set_register(REG_A, 1);
    write(1, 2);

    bool result = ori(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = ori(1);
    ck_assert_int_eq(get_register(REG_A), 3);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(xra_test) {
    set_register(REG_A, 2);
    set_register(REG_B, 2);

    bool result = xra(REG_B);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(xri_test) {
    set_register(REG_A, 2);
    write(1, 2);

    bool result = xri(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = xri(1);
    ck_assert_int_eq(get_register(REG_A), 0);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(cmp_test) {
    set_register(REG_A, 1);
    set_register(REG_B, 1);

    bool result = cmp(REG_B);
    ck_assert_int_eq(result, true);
    ck_assert_int_eq(get_register(REG_A), 1);
}
END_TEST

START_TEST(cpi_test) {
    set_register(REG_A, 1);
    write(1, 1);

    bool result = cpi(0);
    ck_assert_int_eq(get_program_counter(), 1);

    result = cpi(1);
    ck_assert_int_eq(get_register(REG_A), 1);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(rlc_test) {
    set_register(REG_A, 0b0001);
    
    bool result = rlc();
    ck_assert_int_eq(get_register(REG_A), 0b0010);
    ck_assert_int_eq(result, true);
}
END_TEST

START_TEST(rlc_carry) {
    set_register(REG_A, 0b10000001);
    
    ck_assert_int_eq(get_register_bit(REG_F, CARRY), 0);

    bool result = rlc();
    ck_assert_int_eq(get_register(REG_A), 0b00000010);
    ck_assert_int_eq(get_register_bit(REG_F, CARRY), 1);
    ck_assert_int_eq(result, true);
}
END_TEST

#define TEST_CASE_SIZE 100

Suite* arithmetic_instruction_suite(void) {
    Suite* suite;

    suite = suite_create("Arithmetic Instruction");

    char* test_names[TEST_CASE_SIZE] = {
        "ADD",
        "ADD Overflow",
        "ADI",
        "ADI Overflow",
        "ADC No Carry",
        "ADC Carry",
        "ACI No Carry",
        "ACI Carry",
        "SUB",
        "SUB Overflow",
        "SUI",
        "SUI Overflow",
        "SBB No Carry",
        "SBB Carry",
        "SBI No Carry",
        "SBI Carry",
        "INR",
        "INR Overflow",
        "DCR",
        "DCR Auxiliary",
        "DCR Overflow",
        "INX",
        "DCX",
        "DAD",
        "DAD Overflow",
        "DAA",
        "ANA",
        "ANI",
        "ORA",
        "ORI",
        "XRA",
        "XRI",
        "CMP",
        "CPI",
        "RLC",
        "RLC Carry"
    };

    const TTest* test_functions[TEST_CASE_SIZE] = {
        add_test,
        add_overflow,
        adi_test,
        adi_overflow,
        adc_no_carry,
        adc_carry,
        aci_no_carry,
        aci_carry,
        sub_test,
        sub_overflow,
        sui_test,
        sui_overflow,
        sbb_no_carry,
        sbb_carry,
        sbi_no_carry,
        sbi_carry,
        inr_test,
        inr_overflow,
        dcr_test,
        dcr_test_1,
        dcr_overflow,
        inx_test,
        dcx_test,
        dad_test,
        dad_overflow,
        daa_test,
        ana_test,
        ani_test,
        ora_test,
        ori_test,
        xra_test,
        xri_test,
        cmp_test,
        cpi_test,
        rlc_test,
        rlc_carry
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