#include "io/io_controller.h"
#include "unity.h"
#include <stdint.h>

uint8_t loopback_test(uint8_t port_address, uint8_t value, ACCESS_MODE access_mode) { return value + 1; }

void set_a_port_to_a_specific_function() {
    set_input_device(1, loopback_test);
    TEST_ASSERT_EQUAL_INT(2, get_input_device(1)(0, 1, INPUT));
}

void set_multiple_ports_to_the_same_function() {
    set_input_device(1, loopback_test);
    set_input_device(2, loopback_test);
    TEST_ASSERT_EQUAL_INT(2, get_input_device(1)(0, 1, INPUT));
    TEST_ASSERT_EQUAL_INT(11, get_input_device(2)(0, 10, INPUT));
}

void not_run_a_not_assigned_port() { TEST_ASSERT_EQUAL_INT(0, get_input_device(3)(0, 1, INPUT)); }

void read_a_port_value() {
    set_input_device(1, loopback_test);
    TEST_ASSERT_EQUAL_INT(1, read_port(1));
}

void read_and_return_an_invalid_port() { TEST_ASSERT_EQUAL_INT(0, read_port(4)); }

void run_io_controller_test() {
    printf("IO controller:\n");
    RUN_TEST(set_a_port_to_a_specific_function);
    RUN_TEST(set_multiple_ports_to_the_same_function);
    RUN_TEST(not_run_a_not_assigned_port);
    RUN_TEST(read_a_port_value);
    RUN_TEST(read_and_return_an_invalid_port);
}