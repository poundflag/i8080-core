#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "cpu.h"

Running_Mode current_running_mode;
int steps_to_run = 0;

void process_arguments(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp("-i", argv[i]) == 0) {
            printf("Loading file: %s\n", argv[++i]);
            load_file(argv[i], 0);
        }
        else if (strcmp("-o", argv[i]) == 0) {
            printf("Set Output file: %s\n", argv[++i]);
        }
        else if (strcmp("-steps", argv[i]) == 0) {
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
