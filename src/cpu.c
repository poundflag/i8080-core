#include "cpu.h"
#include "memory/memory_controller.h"
#include "register/register_controller.h"
#include "instruction/instruction.h"

bool output_file = false;
char* file_path = "";

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

void step(int* machine_cycle, uint16_t* temporary_address) {
    // Get the current opcode if this is called for the first time
    if (first_start_up == true) {
        current_opcode = read(get_program_counter());
        first_start_up = false;
    }

    // Decode & Execute
    bool result = decode_execute_instruction(current_opcode, *machine_cycle, temporary_address);

    if (result == true) {
        if (output_file == true) {
            char* output = "THIS IS A TEST\n";
            writeStringToFile(output, file_path);
        }
        (*machine_cycle) = 0;
        (*temporary_address) = 0;
        increment_program_counter();
        current_opcode = read(get_program_counter());
    }
    else {
        (*machine_cycle)++;
    }
}

void writeStringToFile(char* input, char* filename) {
    // creating file pointer to work with files
    FILE* fptr;
    // opening file in appending mode
    fptr = fopen(filename, "a");
    // exiting program if file cannot be opened
    if (fptr == NULL) {
        printf("Error opening file!");
        exit(1);
    }
    // writing the string to the file
    fprintf(fptr, "%s", input);
    // closing the file
    fclose(fptr);
}

void load_file(char* file_path, uint16_t address_offset) {
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

    load_memory(file_data, file_size, address_offset);

    // Cleanup: close the file and free the memory
    fclose(file);
    free(file_data);
}
