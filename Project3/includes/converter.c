
#include "../headers/converter.h"

// I crammed it all in here so I wouldn't have to worry about allocating any more memory.
SinglePrecisionFloat *create_single_precision_float(float num) {
	SinglePrecisionFloat *spf_float = malloc(sizeof(SinglePrecisionFloat));
	char temp[32], left_side[32], right_side[32];
	int index = 0, binary_size = 0;
	int integer = (int)num;
	float decimal = num - integer;

	printf("Creating a single precision float from %f\n", num);
	spf_float->o = num;

	// GET SIGN BIT!!!!!
	if(num < 0) {
		spf_float->sign = 1;
		num *= -1;
	} else {
		spf_float->sign = 0;
	}
	printf("Sign bit : %d\n", spf_float->sign);


	// GET THE EXPONENT
	/* ====                      =====*/
	/* ==== LEFT SIDE OF DECIMAL =====*/
	/* ====                      =====*/
	// Initialize buffers
	while (index < 32) {
		*(left_side + index) = '0';
		*(temp + index) = '0';
		*(right_side + index) = '0';
		index++;
	}

	index = 0;

	// Store forward direction in temp.
	while (integer != 0 && index < 32) {
		if ((integer % 2) == 0) { // No remainder
			*(temp + index) = '0';
		}
		else {
			*(temp + index) = '1';
		}
		integer /= 2;
		index++;
		binary_size++;
	}

	//Reverese the direction
	for (int i = 0; i < binary_size; i++) {
		left_side[i] = temp[binary_size - i - 1];
	}

	left_side[binary_size] = '\0';

	printf("Binary representation of left-half: %s of size: %d and exponential shift: %d\n", left_side, binary_size, get_exponent(left_side));
	spf_float->exponent = get_exponent(left_side);

	/* ====                       =====*/
	/* ==== RIGHT SIDE OF DECIMAL =====*/
	/* ====                       =====*/
	// Store forward direction in temp.
	index = 0;
	binary_size = 0;

	while (decimal != 0 && index < 32) {
		if ((decimal * 2) >= 1) { // No remainder
			*(right_side + index) = '1';
			decimal *= 2;
			decimal -= 1;
		}
		else {
			*(right_side + index) = '0';
			decimal *= 2;
		}
		index++;
		binary_size++;
	}

	right_side[binary_size] = '\0';

	printf("Binary representation of right-half: %s\n", right_side);

	return spf_float;
}

void delete_single_precision_float(SinglePrecisionFloat *spf_float) {
  free(spf_float);
}

char *int_to_binary_c(int integer) {
	char temp[32], binary_c[32];
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

	printf("Binary representation of left-half: %s of size: %d and exponential shift: %d\n", binary_c, binary_size, get_exponent(binary_c));
	return binary_c;
}

char *decimal_to_binary_c(float decimal) {
	char binary_c[32];
	int index = 0, binary_size = 0;

	// Initialize buffers
	while (index < 32) {
		*(binary_c + index) = '0';
		index++;
	}

	index = 0;

	// Store forward direction in temp.
	while (decimal != 0 && index < 32) {
		if ((decimal * 2) >= 1) { // No remainder
			*(binary_c + index) = '1';
			decimal *= 2;
			decimal -= 1;
		}
		else {
			*(binary_c + index) = '0';
			decimal *= 2;
		}
		index++;
		binary_size++;
	}

	binary_c[binary_size] = '\0';

	printf("Binary representation of right-half: %s\n", binary_c);

	return binary_c;
}

int get_exponent(char *binary_left_half) {
	int exponent_shift = 0;

	if (binary_left_half[0] == '\0') {
		return 0;
	}
	else if (binary_left_half[1] == '\0') {
		return 0;
	}
	else {
		while (binary_left_half[exponent_shift] != '\0') {
			exponent_shift++;
		}

		return exponent_shift - 1;
	}

}

