#ifndef CONVERTER
#define CONVERTER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float o;
  int sign;
  int exponent;
  int mantissa;
} SinglePrecisionFloat;

SinglePrecisionFloat *create_single_precision_float(float);
void delete_single_precision_float(SinglePrecisionFloat *);

#endif
