#include "unity.h"
#include "../src/cpu.h"
#include "../src/register/stack.h"
#include "../src/register/register_controller.h"

void setUp(void) {
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/EMPTY_ROM.COM", 0);
    set_stack_pointer(0);

    set_register_pair(PAIR_B, 0);
    set_register_pair(PAIR_D, 0);
    set_register_pair(PAIR_H, 0);
    set_register_pair(PAIR_PSW, 0);
    set_register_pair(PAIR_SP, 0);

    set_register(REG_A, 0);
    set_register(REG_B, 0);
    set_register(REG_C, 0);
    set_register(REG_D, 0);
    set_register(REG_E, 0);
    set_register(REG_H, 0);
    set_register(REG_L, 0);
    set_register(REG_F, 2);

    set_program_counter(0);
}
void tearDown(void) {}

void run_cpu_test();
void run_status_service_test();
void run_utils_test();
void run_flag_register_test();
void run_stack_test();
void run_register_controller_test();
void run_memory_controller_test();

int main(void) {
    UNITY_BEGIN();
    run_cpu_test();
    run_status_service_test();
    run_utils_test();
    run_flag_register_test();
    run_stack_test();
    run_register_controller_test();
    run_memory_controller_test();
    return UNITY_END();
}