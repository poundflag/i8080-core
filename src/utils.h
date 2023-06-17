#ifndef _UTILS_H_
#define _UTILS_H_

typedef enum {
    STEPPING,
    INDEFINITE
} Running_Mode;

extern Running_Mode current_running_mode;
extern int steps_to_run;

void process_arguments(int argc, char** argv);

#endif // _UTILS_H_