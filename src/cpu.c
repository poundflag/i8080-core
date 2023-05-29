#include "cpu.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "instruction/instruction.h"

void run_indefinite() {
    while (true) {
        step();
    }
}

void run(int steps) {
    for (int i = 0; i < steps; i++) {
        step();
    }
}

void step() {
    // Read the current address
    uint8_t opcode = read(get_program_counter());

    // Decode & Execute
    decode_execute_instruction(opcode, 0, 0);
}

void load_file(char* file_path) {
    // Open file in binary mode
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Failed to open the file: %s\n", file_path);
        return;
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    uint8_t* file_data = (uint8_t*)malloc(file_size);
    if (file_data == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Read the file contents into the array
    size_t bytes_read = fread(file_data, 1, file_size, file);
    if (bytes_read != file_size) {
        printf("Failed to read the file: %s\n", file_path);
        free(file_data);
        fclose(file);
        return;
    }

    load_memory(file_data, file_size, 0);

    // Cleanup: close the file and free the memory
    fclose(file);
    free(file_data);
}
