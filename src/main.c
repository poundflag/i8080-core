#include "cpu.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  process_arguments(argc, argv);

  if (current_running_mode == INDEFINITE) {
    run_indefinite();
  } else if (current_running_mode == STEPPING) {
    run(steps_to_run);
  }

  return 0;
}