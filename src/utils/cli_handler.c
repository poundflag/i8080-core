#include "utils/cli_handler.h"
#include "cpu.h"
#include <stdio.h>
#include <string.h>

Running_Mode current_running_mode;
int steps_to_run = 0;

typedef enum { ARG_INPUT, ARG_OUTPUT, ARG_STEPS, ARG_HELP, SIZE_ENUM_ARG } arguments;

struct map_struct {
    char *key;
    arguments value;
};

struct map_struct lookup_table[] = {{"-i", ARG_INPUT}, {"-o", ARG_OUTPUT}, {"-s", ARG_STEPS}, {"--help", ARG_HELP}};

int enum_from_string(char *argument) {
    for (int i = 0; i < SIZE_ENUM_ARG; i++) {
        struct map_struct current_map_item = lookup_table[i];
        if (strcmp(current_map_item.key, argument) == 0) {
            return current_map_item.value;
        }
    }
    return -1;
}

void print_help_list() {
    printf(" _   ___    ___    ___    ___                                \n");
    printf("(_) / _ \\  / _ \\  / _ \\  / _ \\                               \n");
    printf(" _ | (_) || | | || (_) || | | | ______  ___  ___   _ __  ___ \n");
    printf("| | > _ < | | | | > _ < | | | ||______|/ __|/ _ \\ | '__|/ _ \\\n");
    printf("| || (_) || |_| || (_) || |_| |       | (__| (_) || |  |  __/\n");
    printf("|_| \\___/  \\___/  \\___/  \\___/         \\___|\\___/ |_|   "
           "\\___|\n\n");

    printf("Call: i8080-core [Arguments]\nOptions:\n");
    printf("\t-i <Path>\tInput file to be loaded in memory\n");
    printf("\t-o <Path>\tOutput file for the debug information from the cpu\n");
    printf("\t-s <number>\tSteps for the cpu to take in machine cycles. \n\t\t\tAn "
           "input of -1 is an infinite run.\n");
    printf("\t--help\t\tPrint the list of available commands\n");
}

bool has_arguments(int argument_count) { return argument_count > 1; }

void decode_and_execute_argument(int *argument_position, char **argument_array, bool *is_invalid_argument) {
    switch (enum_from_string(argument_array[*argument_position])) {
    case ARG_INPUT:
        printf("Loading file: %s\n", argument_array[++(*argument_position)]);
        load_file(argument_array[*argument_position], 0);
        break;
    case ARG_OUTPUT:
        printf("Set Output file: %s\n", argument_array[++(*argument_position)]);
        output_file = true;
        file_path = argument_array[*argument_position];
        break;
    case ARG_STEPS:
        int step_count = atoi(argument_array[++(*argument_position)]);
        if (step_count >= 0) {
            printf("Running cpu for %d steps\n", step_count);
            current_running_mode = STEPPING;
            steps_to_run = step_count;
        } else {
            printf("Running cpu infinite\n");
            current_running_mode = INDEFINITE;
            steps_to_run = -1;
        }
        break;
    case ARG_HELP:
        print_help_list();
        break;
    default:
        printf("%s is an invalid command\n", argument_array[*argument_position]);
        printf("Call --help to get a list of arguments\n");
        *is_invalid_argument = true;
        break;
    }
}

void process_arguments(int argument_count, char **argument_array) {
    if (has_arguments(argument_count)) {
        bool is_invalid_argument = false;
        for (int argument_position = 1; argument_position < argument_count; argument_position++) {
            decode_and_execute_argument(&argument_position, argument_array, &is_invalid_argument);
            if (is_invalid_argument == true) {
                break;
            }
        }
    } else {
        print_help_list();
    }
}
