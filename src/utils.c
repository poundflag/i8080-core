#include "utils.h"
#include "cpu.h"
#include <stdio.h>
#include <string.h>

Running_Mode current_running_mode;
int steps_to_run = 0;

bool is_input_mode(char *arg) { return strcmp("-i", arg) == 0; }

bool is_output_mode(char *arg) { return strcmp("-o", arg) == 0; }

bool is_steps_mode(char *arg) { return strcmp("-s", arg) == 0; }

bool is_help_command(char *arg) { return strcmp("--help", arg) == 0; }

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
  printf(
      "\t-s <number>\tSteps for the cpu to take in machine cycles. \n\t\t\tAn "
      "input of -1 is an infinite run.\n");
  printf("\t--help\t\tPrint the list of available commands\n");
}

void process_arguments(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if (is_input_mode(argv[i]) == true) {
      printf("Loading file: %s\n", argv[++i]);
      load_file(argv[i], 0);
    } else if (is_output_mode(argv[i]) == true) {
      printf("Set Output file: %s\n", argv[++i]);
      output_file = true;
      file_path = argv[i];
    } else if (is_steps_mode(argv[i]) == true) {
      int size = atoi(argv[++i]);
      if (size >= 0) {
        printf("Running cpu for %d steps\n", size);
        current_running_mode = STEPPING;
        steps_to_run = size;
      } else {
        printf("Running cpu infinite\n");
        current_running_mode = INDEFINITE;
        steps_to_run = -1;
      }
    } else if (is_help_command(argv[i]) == true) {
      print_help_list();
    } else {
      printf("%s is an invalid command\n", argv[i]);
      printf("Call --help to get a list of arguments\n");
      break;
    }
  }
  if (argc <= 1) {
    print_help_list();
  }
}
