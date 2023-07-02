#include <stdint.h>

#ifndef _STACK_H_
#define _STACK_H_

uint16_t get_stack_pointer();
void set_stack_pointer(uint16_t stack_pointer_address);
void push_word(uint16_t word_value);
uint16_t pull_word();

#endif //_STACK_H_