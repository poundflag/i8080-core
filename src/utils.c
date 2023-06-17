#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "cpu.h"

Running_Mode current_running_mode;
int steps_to_run = 0;

bool is_input_mode(char* arg) {
    return strcmp("-i", arg) == 0;
}

bool is_output_mode(char* arg) {
    return strcmp("-o", arg) == 0;
}

bool is_steps_mode(char* arg) {
    return strcmp("-steps", arg) == 0;
}

void process_arguments(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (is_input_mode(argv[i]) == true) {
            printf("Loading file: %s\n", argv[++i]);
            load_file(argv[i], 0);
        }
        else if (is_output_mode(argv[i]) == true) {
            printf("Set Output file: %s\n", argv[++i]);
            output_file = true;
            file_path = argv[i];
        }
        else if (is_steps_mode(argv[i]) == true) {
            int size = atoi(argv[++i]);
            if (size >= 0) {
                printf("Running cpu for %d steps\n", size);
                current_running_mode = STEPPING;
                steps_to_run = size;
            }
            else {
                printf("Running cpu infinite\n");
                current_running_mode = INDEFINITE;
                steps_to_run = -1;
            }
        }
        else {
            printf("%s is an invalid command\n", argv[i]);
        }
    }
}
