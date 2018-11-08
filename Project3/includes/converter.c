
#include "../headers/converter.h"

SinglePrecisionFloat *create_single_precision_float(float num) {
	SinglePrecisionFloat *spf_float = malloc(sizeof(SinglePrecisionFloat));

	printf("Creating a single precision float from %f\n", num);
	spf_float->o = num;

	if(num < 0) {
		spf_float->sign = 1;
		num *= -1;
	} else {
		spf_float->sign = 0;
	}

	printf("Sign bit : %d\n", spf_float->sign);
	printf("Binary representation of left-half: %s", int_to_binary_c(num));

  return spf_float;
}

void delete_single_precision_float(SinglePrecisionFloat *spf_float) {
  free(spf_float);
}

char *int_to_binary_c(int integer) {
	char binary_c[32];
	int index = 0;

	while(integer != 0) {
		if((integer/=2) == 0) { // No remainder
			*(binary_c + index) = '0';
		} else {
			*(binary_c + index) = '1';
		}
		index++;
	}

	while(index < 32) {
		*(binary_c + index) = '0';
		index++;
	}

	return binary_c;
}
