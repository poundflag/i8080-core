#include "bus_controller.h"
#include "register/register_controller.h"

uint8_t data_value = 0;

uint16_t get_address_bus() {
    return get_program_counter();
}

uint8_t get_data_bus() {
    return data_value;
}

void set_data_bus(uint8_t value) {
    data_value = value;
}