#include "cpu.h"
#include "io/io_controller.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

uint8_t altair_switch_io_device(uint8_t port_address, uint8_t value, ACCESS_MODE access_mode) { return 0b00100010; }

uint8_t sio_io_device(uint8_t port_address, uint8_t value, ACCESS_MODE access_mode) {
    if (access_mode == INPUT) {
        if (port_address == 0x10 || port_address == 0x0) {
            return 0x02;
        } else if (port_address == 1) {
            // Read keyboard input
            char input; // Assuming a maximum input length of 100 characters
            scanf("%c", &input);

            if (input == 0x0A) {
                return 0x0D;
            }

            // Return the input
            return input;
        }
        return 0;
    } else {
        if (value == '\r') {
            printf(" ");
        } else {
            printf("%c", value);
        }
        fflush(stdout);
    }
    return 0;
}

int main(int argc, char **argv) {
    load_file("/home/robin/Dokumente/Projects/altair-8800/rom/4kbas40.bin", 0);
    set_input_device(0xFF, altair_switch_io_device);

    set_input_device(0, sio_io_device);
    set_input_device(1, sio_io_device);
    set_input_device(0x10, sio_io_device);
    set_input_device(0x11, sio_io_device);

    printf("RUNNING\n");
    fflush(stdout);

    run_indefinite();

    /*process_arguments(argc, argv);

    if (current_running_mode == INDEFINITE) {
        run_indefinite();
    } else if (current_running_mode == STEPPING) {
        run(steps_to_run);
    }*/

    return 0;
}