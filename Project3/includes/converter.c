
#include "../headers/converter.h"

// I crammed it all in here so I wouldn't have to worry about allocating any more memory.
SinglePrecisionFloat *create_single_precision_float(float num) {
	SinglePrecisionFloat *spf_float = malloc(sizeof(SinglePrecisionFloat));
	char temp[32], left_side[32], right_side[32], mantissa_c[23];
	int index = 0, left_size = 0, right_size = 0;
	int integer = (int)num;
	float decimal = num - integer;

	printf("Creating a single precision float from %f\n", num);
	spf_float->o = num;

	// GET SIGN BIT!!!!!
	if(num < 0) {
		spf_float->sign = create_binary_representation(1, 1);
		num *= -1;
	} else {
		spf_float->sign = create_binary_representation(0, 1);
	}
	printf("Sign bit : %s\n", spf_float->sign);


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
		left_size++;
	}

	//Reverese the direction
	for (int i = 0; i < left_size; i++) {
		left_side[i] = temp[left_size - i - 1];
	}

	left_side[left_size] = '\0';

	printf("Binary representation of left-half: %s of size: %d and exponential shift: %d\n", left_side, left_size, get_exponent(left_side));
	spf_float->exponent = create_binary_representation(get_exponent(left_side), 8);

	/* ====                       =====*/
	/* ==== RIGHT SIDE OF DECIMAL =====*/
	/* ====                       =====*/
	// Store forward direction in temp.
	index = 0;

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
		right_size++;
	}

	right_side[right_size] = '\0';
	printf("Binary representation of right-half: %s\n", right_side);

	/* ====                       =====*/
	/* ======= CREATE MANTISSA ========*/
	/* ====                       =====*/
	index = 0;

	print_float(spf_float);

	return spf_float;
}

void print_float(SinglePrecisionFloat *spf_float) {
	if (spf_float == NULL) {
		printf("This is a NULL object.  Cannot print.\n");
	}
	else {
		printf("Decimal value: %f, sign: %s, exponent: %s, mantissa: %s\n", spf_float->o, spf_float->sign, spf_float->exponent, spf_float->mantissa);
	}
}

void delete_single_precision_float(SinglePrecisionFloat *spf_float) {
	free(spf_float->sign);
	free(spf_float->exponent);
	free(spf_float->mantissa);
	free(spf_float);
}

char *create_binary_representation(int integer, int bits) {
	char temp[32], binary_c[32];
	int index = 0, binary_size = 0, difference = 0, initial = integer;
	char *binary_representation;

	// Initialize buffers
	while (index < 32) {
		*(binary_c + index) = '0';
		*(temp + index) = '0';
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
		binary_c[i] = temp[binary_size - i - 1];
	}

	binary_representation = strndup(binary_c, bits);

	printf("Binary representation of %d is %s\n", initial, binary_representation);
	return binary_representation;
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

	while (binary_left_half[exponent_shift] != '\0') {
		exponent_shift++;
	}

	return exponent_shift - 1 + 127;

}

