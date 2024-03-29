#include "bus_controller.h"
#include "instruction/arithmetic_instruction.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "unity.h"
#include <stdbool.h>

void test_add_test() {
    set_register(REG_A, 0x12);
    set_register(REG_B, 0x12);

    bool result = add(REG_B);
    TEST_ASSERT_EQUAL_INT(0x24, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000110, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_add_overflow() {
    set_register(REG_A, 0xFF);
    set_register(REG_B, 0x10);

    bool result = add(REG_B);
    TEST_ASSERT_EQUAL_INT(0xF, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000111, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_adi_test() {
    set_program_counter(0);
    write_to_memory(1, 0x12);
    set_register(REG_A, 0x12);

    bool result = adi(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x12, get_data_bus());

    result = adi(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x24, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000110, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_adi_overflow() {
    set_program_counter(0);
    write_to_memory(1, 0xFF);
    set_register(REG_A, 0x10);

    bool result = adi(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0xFF, get_data_bus());

    result = adi(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0xF, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000111, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_adc_no_carry() {
    set_register(REG_A, 1);
    set_register(REG_B, 1);
    set_register_bit(REG_F, CARRY, false);

    bool result = adc(REG_B);
    TEST_ASSERT_EQUAL_INT(0x2, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000010, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_adc_carry() {
    set_register(REG_A, 1);
    set_register(REG_B, 1);
    set_register_bit(REG_F, CARRY, true);

    bool result = adc(REG_B);
    TEST_ASSERT_EQUAL_INT(0x3, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000110, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_aci_no_carry() {
    set_program_counter(0);
    write_to_memory(1, 1);
    set_register(REG_A, 1);
    set_register_bit(REG_F, CARRY, false);

    bool result = aci(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(1, get_data_bus());

    result = aci(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x2, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000010, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_aci_carry() {
    set_program_counter(0);
    write_to_memory(1, 1);
    set_register(REG_A, 1);
    set_register_bit(REG_F, CARRY, true);

    bool result = aci(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(1, get_data_bus());

    result = aci(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x3, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00000110, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_sub_test() {
    set_register(REG_A, 5);
    set_register(REG_B, 1);

    bool result = sub(REG_B);
    TEST_ASSERT_EQUAL_INT(4, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00010010, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_sub_overflow() {
    set_register(REG_A, 1);
    set_register(REG_B, 5);

    bool result = sub(REG_B);
    TEST_ASSERT_EQUAL_INT(0xFC, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b10000111, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_sui_test() {
    set_program_counter(0);
    write_to_memory(1, 1);
    set_register(REG_A, 5);

    bool result = sui(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(1, get_data_bus());

    result = sui(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(4, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b00010010, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_sui_overflow() {
    set_program_counter(0);
    write_to_memory(1, 5);
    set_register(REG_A, 1);

    bool result = sui(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(5, get_data_bus());

    result = sui(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0xFC, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(0b10000111, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_sbb_no_carry() {
    set_register(REG_A, 5);
    set_register(REG_B, 1);
    set_register_bit(REG_F, CARRY, false);

    bool result = sbb(REG_B);
    TEST_ASSERT_EQUAL_INT(0x4, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_sbb_carry() {
    set_register(REG_A, 5);
    set_register(REG_B, 1);
    set_register_bit(REG_F, CARRY, true);

    bool result = sbb(REG_B);
    TEST_ASSERT_EQUAL_INT(0x3, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_sbi_no_carry() {
    set_program_counter(0);
    write_to_memory(1, 1);
    set_register(REG_A, 5);
    set_register_bit(REG_F, CARRY, false);

    bool result = sbi(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(1, get_data_bus());

    result = sbi(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x4, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_sbi_carry() {
    set_program_counter(0);
    write_to_memory(1, 1);
    set_register(REG_A, 5);
    set_register_bit(REG_F, CARRY, true);

    bool result = sbi(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(1, get_data_bus());

    result = sbi(1);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(0x3, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_inr_test() {
    set_register(REG_B, 1);

    bool result = inr(REG_B);
    TEST_ASSERT_EQUAL_INT(2, get_register(REG_B));
    TEST_ASSERT_TRUE(result);
}

void test_inr_overflow() {
    set_register(REG_B, 0xFF);

    bool result = inr(REG_B);
    TEST_ASSERT_EQUAL_INT(0, get_register(REG_B));
    TEST_ASSERT_EQUAL_INT(0b01010110, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_dcr_test() {
    set_register(REG_B, 1);

    bool result = dcr(REG_B);
    TEST_ASSERT_EQUAL_INT(0, get_register(REG_B));
    TEST_ASSERT_TRUE(result);
}

void test_dcr_test_1() {
    set_register(REG_B, 2);

    bool result = dcr(REG_B);
    TEST_ASSERT_EQUAL_INT(1, get_register(REG_B));
    TEST_ASSERT_EQUAL_INT(1, (get_register(REG_F) >> 4) & 1);
    TEST_ASSERT_TRUE(result);
}

void test_dcr_overflow() {
    set_register(REG_B, 0);

    bool result = dcr(REG_B);
    TEST_ASSERT_EQUAL_INT(0xFF, get_register(REG_B));
    TEST_ASSERT_EQUAL_INT(0b10000110, get_register(REG_F));
    TEST_ASSERT_TRUE(result);
}

void test_inx_test() {
    set_register_pair(PAIR_B, 0x44);

    bool result = inx(PAIR_B);
    TEST_ASSERT_EQUAL_INT(0x45, get_register_pair(PAIR_B));
    TEST_ASSERT_TRUE(result);
}

void test_dcx_test() {
    set_register_pair(PAIR_B, 0x44);

    bool result = dcx(PAIR_B);
    TEST_ASSERT_EQUAL_INT(0x43, get_register_pair(PAIR_B));
    TEST_ASSERT_TRUE(result);
}

void test_dad_test() {
    set_register_pair(PAIR_H, 0x1234);
    set_register_pair(PAIR_B, 0x1234);

    bool result = dad(PAIR_B);
    TEST_ASSERT_EQUAL_INT(0x2468, get_register_pair(PAIR_H));
    TEST_ASSERT_TRUE(result);
}

void test_dad_overflow() {
    set_register_pair(PAIR_H, 0xFFFF);
    set_register_pair(PAIR_B, 0x4444);

    bool result = dad(PAIR_B);
    TEST_ASSERT_EQUAL_INT(0x4443, get_register_pair(PAIR_H));
    TEST_ASSERT_EQUAL_INT(1, get_register(REG_F) & 1);
    TEST_ASSERT_TRUE(result);
}

void test_daa_test() {
    bool result = daa();
    TEST_ASSERT_TRUE(result);
}

void test_ana_test() {
    set_register(REG_A, 4);
    set_register(REG_B, 6);

    bool result = ana(REG_B);
    TEST_ASSERT_EQUAL_INT(4, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_ani_test() {
    set_register(REG_A, 4);
    write_to_memory(1, 6);

    bool result = ani(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(6, get_data_bus());

    result = ani(1);
    TEST_ASSERT_EQUAL_INT(4, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_ora_test() {
    set_register(REG_A, 1);
    set_register(REG_B, 2);

    bool result = ora(REG_B);
    TEST_ASSERT_EQUAL_INT(3, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_ori_test() {
    set_register(REG_A, 1);
    write_to_memory(1, 2);

    bool result = ori(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(2, get_data_bus());

    result = ori(1);
    TEST_ASSERT_EQUAL_INT(3, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_xra_test() {
    set_register(REG_A, 2);
    set_register(REG_B, 2);

    bool result = xra(REG_B);
    TEST_ASSERT_EQUAL_INT(0, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_xri_test() {
    set_register(REG_A, 2);
    write_to_memory(1, 2);

    bool result = xri(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(2, get_data_bus());

    result = xri(1);
    TEST_ASSERT_EQUAL_INT(0, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_cmp_test() {
    set_register(REG_A, 1);
    set_register(REG_B, 1);

    bool result = cmp(REG_B);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL_INT(1, get_register(REG_A));
}

void test_cpi_test() {
    set_register(REG_A, 1);
    write_to_memory(1, 1);

    bool result = cpi(0);
    TEST_ASSERT_EQUAL_INT(1, get_address_bus());
    TEST_ASSERT_EQUAL_INT(1, get_data_bus());

    result = cpi(1);
    TEST_ASSERT_EQUAL_INT(1, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_rlc_test() {
    set_register(REG_A, 0b0001);

    bool result = rlc();
    TEST_ASSERT_EQUAL_INT(0b0010, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_rlc_carry() {
    set_register(REG_A, 0b10000001);

    TEST_ASSERT_EQUAL_INT(0, get_register_bit(REG_F, CARRY));

    bool result = rlc();
    TEST_ASSERT_EQUAL_INT(0b00000011, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(1, get_register_bit(REG_F, CARRY));
    TEST_ASSERT_TRUE(result);
}

void test_rrc_test() {
    set_register(REG_A, 0b0010);

    bool result = rrc();
    TEST_ASSERT_EQUAL_INT(0b0001, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_rrc_carry() {
    set_register(REG_A, 0b10000001);

    TEST_ASSERT_EQUAL_INT(0, get_register_bit(REG_F, CARRY));

    bool result = rrc();
    TEST_ASSERT_EQUAL_INT(0b11000000, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(1, get_register_bit(REG_F, CARRY));
    TEST_ASSERT_TRUE(result);
}

void test_ral_test() {
    set_register(REG_A, 0b0001);

    bool result = ral();
    TEST_ASSERT_EQUAL_INT(0b0010, get_register(REG_A));
    TEST_ASSERT_TRUE(result);

    set_register_bit(REG_F, CARRY, true);
    result = ral();
    TEST_ASSERT_EQUAL_INT(0b0101, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_ral_carry() {
    set_register(REG_A, 0b10000001);

    TEST_ASSERT_EQUAL_INT(0, get_register_bit(REG_F, CARRY));

    bool result = ral();
    TEST_ASSERT_EQUAL_INT(0b00000010, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(1, get_register_bit(REG_F, CARRY));
    TEST_ASSERT_TRUE(result);
}

void test_rar_test() {
    set_register(REG_A, 0b0100);

    bool result = rar();
    TEST_ASSERT_EQUAL_INT(0b0010, get_register(REG_A));
    TEST_ASSERT_TRUE(result);

    set_register_bit(REG_F, CARRY, true);
    result = rar();
    TEST_ASSERT_EQUAL_INT(0b10000001, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_rar_carry() {
    set_register(REG_A, 0b10000001);

    TEST_ASSERT_EQUAL_INT(0, get_register_bit(REG_F, CARRY));

    bool result = rar();
    TEST_ASSERT_EQUAL_INT(0b01000000, get_register(REG_A));
    TEST_ASSERT_EQUAL_INT(1, get_register_bit(REG_F, CARRY));
    TEST_ASSERT_TRUE(result);
}

void test_cma_test() {
    set_register(REG_A, 0x0F);
    bool result = cma();
    TEST_ASSERT_EQUAL_INT(0xF0, get_register(REG_A));
    TEST_ASSERT_TRUE(result);
}

void test_cmc_test() {
    set_register_bit(REG_F, CARRY, true);
    bool result = cmc();
    TEST_ASSERT_EQUAL_INT(get_register_bit(REG_F, CARRY), false);
    TEST_ASSERT_TRUE(result);
}

void test_stc_test() {
    set_register_bit(REG_F, CARRY, false);
    bool result = stc();
    TEST_ASSERT_EQUAL_INT(get_register_bit(REG_F, CARRY), true);
    TEST_ASSERT_TRUE(result);
}

void run_arithmetic_instruction_test() {
    printf("Arithmetic instruction:\n");
    RUN_TEST(test_add_test);
    RUN_TEST(test_add_overflow);
    RUN_TEST(test_adi_test);
    RUN_TEST(test_adi_overflow);
    RUN_TEST(test_adc_no_carry);
    RUN_TEST(test_adc_carry);
    RUN_TEST(test_aci_no_carry);
    RUN_TEST(test_aci_carry);
    RUN_TEST(test_sub_test);
    RUN_TEST(test_sub_overflow);
    RUN_TEST(test_sui_test);
    RUN_TEST(test_sui_overflow);
    RUN_TEST(test_sbb_no_carry);
    RUN_TEST(test_sbb_carry);
    RUN_TEST(test_sbi_no_carry);
    RUN_TEST(test_sbi_carry);
    RUN_TEST(test_inr_test);
    RUN_TEST(test_inr_overflow);
    RUN_TEST(test_dcr_test);
    RUN_TEST(test_dcr_test_1);
    RUN_TEST(test_dcr_overflow);
    RUN_TEST(test_inx_test);
    RUN_TEST(test_dcx_test);
    RUN_TEST(test_dad_test);
    RUN_TEST(test_dad_overflow);
    RUN_TEST(test_daa_test);
    RUN_TEST(test_ana_test);
    RUN_TEST(test_ani_test);
    RUN_TEST(test_ora_test);
    RUN_TEST(test_ori_test);
    RUN_TEST(test_xra_test);
    RUN_TEST(test_xri_test);
    RUN_TEST(test_cmp_test);
    RUN_TEST(test_cpi_test);
    RUN_TEST(test_rlc_test);
    RUN_TEST(test_rlc_carry);
    RUN_TEST(test_rrc_test);
    RUN_TEST(test_rrc_carry);
    RUN_TEST(test_ral_test);
    RUN_TEST(test_ral_carry);
    RUN_TEST(test_rar_test);
    RUN_TEST(test_rar_carry);
    RUN_TEST(test_cma_test);
    RUN_TEST(test_cmc_test);
    RUN_TEST(test_stc_test);
}