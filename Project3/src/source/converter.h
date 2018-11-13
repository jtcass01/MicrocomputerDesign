#ifndef CONVERTER
#define CONVERTER

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "constants.h"

uint32_t hex_from_float(float);
float create_single_precision_float_from_hex(uint32_t);
char get_mask_value(uint32_t, int);

char *create_binary_representation(int , int );

int get_exponent_from_float(char *, int);
int get_exponent_from_hex(char *);
uint32_t get_hex(char *, char *, char *);
float get_float(char *, char *, char *);
int binary_to_int(char *);

#endif
