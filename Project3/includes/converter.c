
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
	decimal_to_binary_c(num - (int)num);
	int_to_binary_c(num);

	return spf_float;
}

void delete_single_precision_float(SinglePrecisionFloat *spf_float) {
  free(spf_float);
}

char *int_to_binary_c(int integer) {
	char binary_c[32], temp[32];
	int index = 0, binary_size = 0;

	// Initialize buffers
	while(index < 32) {
		*(binary_c + index) = '0';
		*(temp + index) = '0';
		index++;
	}

	index = 0;

	// Store forward direction in temp.
	while(integer != 0 && index < 32) {
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

	binary_c[binary_size] = '\0';

	printf("Binary representation of left-half: %s of size: %d\n", binary_c, binary_size);
	return binary_c;
}

char *decimal_to_binary_c(float decimal) {
	char binary_c[32], temp[32];
	int index = 0, binary_size = 0;

	// Initialize buffers
	while (index < 32) {
		*(binary_c + index) = '0';
		*(temp + index) = '0';
		index++;
	}

	index = 0;

	// Store forward direction in temp.
	while (decimal != 0 && index < 32) {
		if ((decimal * 2) >= 1) { // No remainder
			*(temp + index) = '1';
			decimal *= 2;
			decimal -= 1;
		}
		else {
			*(temp + index) = '0';
			decimal *= 2;
		}
		index++;
		binary_size++;
	}

	//Reverese the direction
	for (int i = 0; i < binary_size; i++) {
		binary_c[i] = temp[binary_size - i - 1];
	}

	binary_c[binary_size] = '\0';

	printf("Binary representation of right-half: %s\n", binary_c);

	return binary_c;
}

