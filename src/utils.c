#include "utils.h"
#include <stdio.h>
#include <string.h>

void process_arguments(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        if (strcmp("-i", argv[i]) == 0) {
            printf("Loaded file: %s\n", argv[++i]);
        } else if (strcmp("-o", argv[i]) == 0) {
            printf("Set Output file: %s\n", argv[++i]);
        } else if (strcmp("-steps", argv[i]) == 0) {
            int size = atoi(argv[++i]);
            if (size >= 0) {
            printf("Running cpu for %d steps\n", size);
            } else {
            printf("Running cpu infinite\n");    
            }
        }
        else {
            printf("%s is an invalid command\n", argv[i]);
        }
    }
}
