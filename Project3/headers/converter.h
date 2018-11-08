#ifndef CONVERTER
#define CONVERTER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float o;
  char sign[1];
  char exponent[8];
  char mantissa[23];
} SinglePrecisionFloat;

SinglePrecisionFloat *create_single_precision_float(float);
void print_float(SinglePrecisionFloat *);
void delete_single_precision_float(SinglePrecisionFloat *);

char *int_to_binary_c(int);
char *decimal_to_binary_c(float);

int get_exponent(char *);

#endif
