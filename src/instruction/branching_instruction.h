#include <stdint.h>
#include <stdbool.h>
#include "../memory/memory_controller.h"
#include "../register/register_controller.h"

#ifndef _BRANCHING_INSTRUCTION_H_
#define _BRANCHING_INSTRUCTION_H_

typedef enum {
    COND_CARRY,
    COND_NO_CARRY,
    COND_MINUS,
    COND_POSITIVE,
    COND_PARITY_EVEN,
    COND_PARITY_ODD,
    COND_ZERO,
    COND_NOT_ZERO
} Condition;

// JMP a     11000011 lb hb    -       Unconditional jump
bool jmp(int machine_cycle, uint16_t* temporary_address);

// Jccc a    11CCC010 lb hb    -       Conditional jump
bool jmp_conditional(int machine_cycle, uint16_t* temporary_address, Condition condition);

// CALL a    11001101 lb hb    -       Unconditional subroutine call
bool call(int machine_cycle, uint16_t* temporary_address);


#endif //_BRANCHING_INSTRUCTION_H_