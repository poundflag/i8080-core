#include "../memory/memory_controller.h"
#include "../register/register_controller.h"
#include <stdbool.h>
#include <stdint.h>

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
bool jmp(int machine_cycle, uint16_t *temporary_address);

// Jccc a    11CCC010 lb hb    -       Conditional jump
bool jmp_conditional(int machine_cycle, uint16_t *temporary_address,
                     Condition condition);

// CALL a    11001101 lb hb    -       Unconditional subroutine call
bool call(int machine_cycle, uint16_t *temporary_address);

// Cccc a    11CCC100 lb hb    -       Conditional subroutine call
bool call_conditional(int machine_cycle, uint16_t *temporary_address,
                      Condition condition);

// RET       11001001          -       Unconditional return from subroutine
bool ret();

// Rccc      11CCC000          -       Conditional return from subroutine
bool ret_conditional(Condition condition);

// PCHL      11101001          -       Jump to address in H:L
bool pchl();

#endif //_BRANCHING_INSTRUCTION_H_