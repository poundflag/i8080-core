#include "../include/cpu.h"
#include "../include/file_io.h"
#include "../include/instruction/instruction.h"
#include "../include/memory/memory_controller.h"
#include "../include/register/register_controller.h"
#include "../include/status_service.h"

bool output_file = false;
char *file_path = "";

int machine_cycle = 0;
uint16_t temporary_address = 0;
uint8_t current_opcode = 0;
bool first_start_up = true;

void run_indefinite() {
    while (true) {
        step(&machine_cycle, &temporary_address);
    }
}

void run(int steps) {
    for (int i = 0; i < steps; i++) {
        step(&machine_cycle, &temporary_address);
    }
}

void step(int *machine_cycle, uint16_t *temporary_address) {
    // Get the current opcode if this is called for the first time
    if (first_start_up == true) {
        current_opcode = read(get_program_counter());
        first_start_up = false;
    }

    // Decode & Execute
    bool result = decode_execute_instruction(current_opcode, *machine_cycle, temporary_address);

    if (result == true) {
        if (output_file == true) {
            char *output = malloc(100);
            snprintf(output, 100, "A=%X B=%X C=%X D=%X E=%X H=%X L=%X F=%X SP=%X PC=%X\n", get_register(REG_A), get_register(REG_B),
                     get_register(REG_C), get_register(REG_D), get_register(REG_E), get_register(REG_H), get_register(REG_L), get_register(REG_F),
                     get_register_pair(PAIR_SP), get_program_counter());
            write_string_to_file(output, file_path);
            free(output);
        }
        set_first_machine_cycle(true);
        (*machine_cycle) = 0;
        (*temporary_address) = 0;
        increment_program_counter();
        current_opcode = read(get_program_counter());
    } else {
        set_first_machine_cycle(false);
        (*machine_cycle)++;
    }
}

void load_file(char *file_path, uint16_t address_offset) {
    File_Response file_response = read_binary_from_file(file_path);
    if (file_response.file_data != NULL && file_response.file_size != -1) {
        load_memory(file_response.file_data, file_response.file_size, address_offset);
        free(file_response.file_data);
    }
}