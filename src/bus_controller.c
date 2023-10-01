#include "bus_controller.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "status_service.h"

uint16_t get_address_bus() {
    if (is_device_input() || is_device_output()) {
        uint8_t input_port = read_from_memory(get_program_counter());
        return input_port | (input_port << 8);
    } else if (has_system_halted()) {
        return 0xFF;
    }
    return get_program_counter();
}

uint8_t get_data_bus() {
    if (!is_write_output() || has_system_halted()) {
        return 0xFF;
    } else if (is_device_input()) {
        return get_register(REG_A);
    }
    return read_from_memory(get_program_counter());
}