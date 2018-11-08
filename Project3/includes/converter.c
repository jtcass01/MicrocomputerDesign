
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

	int_to_binary_c(num);

	return spf_float;
}

void delete_single_precision_float(SinglePrecisionFloat *spf_float) {
  free(spf_float);
}

char *int_to_binary_c(int integer) {
	char binary_c[32], temp[32];
	int index = 0, binary_size = 0;

	while(index < 32) {
		*(binary_c + index) = '0';
		*(temp + index) = '0';
		index++;
	}

	index = 0;

	printf("Binary representation of left-half: %s\n", binary_c);


	// Store forward direction in temp.
	while(integer != 0) {
		if((integer%2) == 0) { // No remainder
			*(temp + index) = '0';
		} else {
			*(temp + index) = '1';
		}
		integer /= 2;
		index++;
		binary_size++;
	}

	//Reverese the direction
	for(int i = 0; i < binary_size; i++) {
		binary_c[i] = temp[binary_size - i - 1];
	}

	binary_c[i] = '\0';

	printf("Binary representation of left-half: %s of size: %d\n", binary_c, binary_size);
	return binary_c;
}
