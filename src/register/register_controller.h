#include <stdint.h>

#ifndef _REGISTER_CONTROLLER_H_
#define _REGISTER_CONTROLLER_H_

typedef enum {
    A,
    B,
    C,
    D,
    E,
    H,
    L,
    F,
    ARRAY_SIZE
} Register;

extern uint8_t register_array[ARRAY_SIZE];

#endif //_REGISTER_CONTROLLER_H_