#include "io/io_controller.h"
#include <stddef.h>

uint8_t unassigned_port(uint8_t port_address, uint8_t value, ACCESS_MODE access_mode) { return 0; }

IO_Device io_devices[0xFF] = {NULL};

IO_Device get_input_device(uint8_t port_address) {
    if (io_devices[port_address] != NULL) {
        return io_devices[port_address];
    }
    return unassigned_port;
}

void set_input_device(uint8_t port_address, IO_Device io_device) { io_devices[port_address] = io_device; }

uint8_t read_port(uint8_t port_address) { return get_input_device(port_address)(port_address, 0, INPUT); }

void write_port(uint8_t port_address, uint8_t value) { return get_input_device(port_address)(port_address, value, OUTPUT); }