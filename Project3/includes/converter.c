
#include "../headers/converter.h"

SinglePrecisionFloat *create_single_precision_float(float num) {
	SinglePrecisionFloat *spf_float = malloc(sizeof(SinglePrecisionFloat));

  printf("Creating a single precision float from %f", num);
  spf_float->o = num; 

  return spf_float;
}

void delete_single_precision_float(SinglePrecisionFloat *spf_float) {
  free(spf_float);
}
