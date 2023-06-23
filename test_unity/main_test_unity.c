#include "unity.h"
#include "../src/cpu.h"

void setUp(void) {
    load_file("/home/robin/Dokumente/Projects/i8080-core/rom/EMPTY_ROM.COM", 0);
}
void tearDown(void) {}

void run_cpu_test();
void run_status_service_test();

int main(void) {
    UNITY_BEGIN();
    run_cpu_test();
    run_status_service_test();
    return UNITY_END();
}