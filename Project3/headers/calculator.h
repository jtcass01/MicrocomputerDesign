#ifndef CALCULATOR
#define CALCULATOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"
#include "constants.h"

int menu(void);
void prompt_convert_number(void);
void prompt_add(void);
void prompt_subtract(void);
void prompt_multiply(void);
void prompt_divide(void);
void prompt_volume(void);

uint32_t add(uint32_t, uint32_t);
uint32_t subtract(uint32_t, uint32_t);
uint32_t multiply(uint32_t, uint32_t);
uint32_t divide(uint32_t, uint32_t);

#endif
