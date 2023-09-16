#include "bus_controller.h"
#include "register/register_controller.h"
#include "memory/memory_controller.h"
#include "status_service.h"

uint16_t get_address_bus() {
    return get_program_counter();
}

uint8_t get_data_bus() {
    if (!is_write_output()) {
        return 0xFF;
    }
    return read_from_memory(get_program_counter());
}