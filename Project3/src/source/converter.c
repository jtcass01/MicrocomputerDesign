
#include "converter.h"

// I crammed it all in here so I wouldn't have to worry about allocating any more memory.


float create_single_precision_float_from_hex(uint32_t hex_value) {
	
	char sign[2], exponent[9], mantissa[24];
	int index = 0;

	#if DEBUG
		printf("Creating SPF_Float from Hex value %X\n", hex_value);
	#endif

	sign[0] = get_mask_value(hex_value, 31-index);
	sign[1] = '\0';
	index++;

	#if DEBUG
		printf("Sign = %s\n", sign);
	#endif

	for (int i = 0; i < 8; i++) {
		exponent[i] = get_mask_value(hex_value, 31 - index);
		index++;
	}
	exponent[8] = '\0';
	#if DEBUG
		printf("Exponent = %s\n", exponent);
	#endif

	for (int i = 0; i < 23; i++) {
		mantissa[i] = get_mask_value(hex_value, 31 - index);
		index++;
	}
	mantissa[23] = '\0';
	#if DEBUG
		printf("Mantissa = %s\n", mantissa);
	#endif


	#if DEBUG
		print_float(spf_float);
	#endif

	float o =  get_float(sign,exponent,mantissa);

	#if DEBUG
		print_float(spf_float);
	#endif

	return o;
}

char get_mask_value(uint32_t hex_value, int bit) {
	if ( (hex_value >> bit) & 1 ) {
		return '1';
	}
	else {
		return '0';
	}
}


int get_exponent_from_float(char *binary_left_half, int negative) {
	int exponent_shift = 0;

	if (negative) {
		while (binary_left_half[exponent_shift] != '\0') {
			exponent_shift++;
			if (binary_left_half[exponent_shift] == '1') {
				break;
			}
		}

		exponent_shift *= -1;
	}
	else {
		while (binary_left_half[exponent_shift] != '\0') {
			exponent_shift++;
		}

	}

	return exponent_shift - 1 + 127;
}


int get_exponent_from_hex(char *binary_exponent) {
	return binary_to_int(binary_exponent) - 127;
}


uint32_t get_hex(char *sign, char *exponent, char *mantissa) {
	uint32_t result = 0;
	int two_power = 0;

	for (int i = 22; i >= 0; i--) {
		if (mantissa[i] == '1') {
			result += (1 << two_power);
		}
		two_power++;
	}

	for (int i = 7; i >= 0; i--) {
		if (exponent[i] == '1') {
			result += (1 << two_power);
		}
		two_power++;
	}

	for (int i = 0; i >= 0; i--) {
		if (sign[i] == '1') {
			result += (1 << two_power);
		}
		two_power++;
	}

	return result;
}

float get_float(char *sign, char *exponent, char *mantissa) {
	float result = 0.0, mantissa_float = 0.0;
	int exponent_integer = 0, left_size = 0, index = 0;
	char left_side[32], right_side[32], temp[32];
	
	exponent_integer = get_exponent_from_hex(exponent);

	#if DEBUG
		printf("Exponent Integer: %d\n", exponent_integer);
	#endif

	// Initialize Buffers
	while (index < 32) {
		*(left_side + index) = '0';
		*(temp + index) = '0';
		*(right_side + index) = '0';
		index++;
	}

	/* ====                      =====*/
	/* ==== LEFT SIDE OF DECIMAL =====*/
	/* ====                      =====*/

	// Store forward direction in temp.
	if (exponent_integer < 0) {
		result = 0.0;
		left_size++;
		index = 1;
	}
	else {
		left_side[0] = '1';
		left_size++;
		index = 1;
		#if DEBUG
			printf("left_side[0] = 1\n");
		#endif

		for (int i = 0; i < exponent_integer; i++) {
			#if DEBUG
				printf("left_side[%d] = mantissa[%d] = %c\n", index, i, mantissa[i]);
			#endif

			left_side[index] = mantissa[i];
			left_size++;
			index++;
		}


	}
	left_side[index+1] = '\0';
	result += (float) binary_to_int(left_side); 

	#if DEBUG
		printf("LeftSide Binary: %s | LeftSide Integer: %f\n", LeftSide, result);
	#endif

	/* ====                       =====*/
	/* ==== RIGHT SIDE OF DECIMAL =====*/
	/* ====                       =====*/
	if (left_side[0] == '0') { // Decimal only case
		for (int i = 0; mantissa[i] != '\0'; i++) {
			if (mantissa[i] == '1') {
				mantissa_float += ((float) 1 / (float) (1 << (i + 1)));

				#if DEBUG
					printf("1 found @ %d - adding %f or 1 / %d to result\n", i, mantissa_float, (1 << (i + 1)));
				#endif
			}
		}
		mantissa_float += 1.0;

		#if DEBUG
			printf("Manitssa float = %f\n", mantissa_float + 1.0);
		#endif

		for(int i = 0; i < (-1*exponent_integer); i++) {
			mantissa_float /= 2.0;
		}

		#if DEBUG
			printf("Manitssa float = %f\n", mantissa_float);
		#endif

		result = mantissa_float;
	}
	else {
		for (int i = exponent_integer; mantissa[i] != '\0'; i++) {
			if (mantissa[i] == '1') {
				mantissa_float = ((float)1 / (float)(1 << (i - exponent_integer + 1)));

				#if DEBUG
					printf("1 found @ %d - adding %f or 1 / %d to result\n", i, mantissa_float, (1 << (i - exponent_integer + 1)));
				#endif

				result += mantissa_float;
			}
		}
	}

	#if DEBUG
		printf("Result with decimal: %f\n", result);
	#endif



	// Apply sign.
	if (sign[0] == '1') {
		result *= -1;
	}


	return result;
}

int binary_to_int(char *binary_num) {
	int result = 0, size = 0, index = 0;

	for (int i = 0; *(binary_num + i) != '\0'; i++) {
		size++;
	}

	for (int i = size - 1; i >= 0; i--) {
		if (binary_num[i] == '1') {
			result += (1 << index);
		}
		index++;
	}

	return result;
}
uint32_t hex_from_float(float num) {
  char temp[32], left_side[32], exponent[9], right_side[32], mantissa_c[24], sign[2];
	int index = 0, left_size = 0, right_size = 0, exponent_i = 0;
	char *LeftSide, *RightSide;

  // GET SIGN BIT!!!!!
	if(num < 0) {
    sign[0] = '1';
		num *= -1;
	} else {
    sign[0] = '0';
	}

  sign[1] = '\0';

  int integer = (int)num;
	float decimal = num - integer;

  // GET THE EXPONENT
	/* ====                      =====*/
	/* ==== LEFT SIDE OF DECIMAL =====*/
	/* ====                      =====*/
	// Initialize buffers
	while (index < 32) {
		*(left_side + index) = '0';
		*(temp + index) = '0';
		*(right_side + index) = '0';
		if (index < 23) {
			*(mantissa_c + index) = '0';
		}
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

  left_side[left_size + 1] = '\0';

  // Store exponent.
	if (left_size != 0) {
    exponent_i = get_exponent_from_float(left_side, 0);
    // Create binary represenation for exponent
  	int index_e = 0, binary_size_e = 0;

    // Initialize buffers
  	while (index_e < 8) {
  		*(exponent + index_e) = '0';
  		*(temp + index_e) = '0';
  		index_e++;
  	}

  	index_e = 0;

  	// Store forward direction in temp.
  	while (exponent_i != 0 && index_e < 8) {
  		if ((exponent_i % 2) == 0) { // No remainder
  			*(temp + index_e) = '0';
  		}
  		else {
  			*(temp + index_e) = '1';
  		}
  		exponent_i /= 2;
  		index_e++;
  		binary_size_e++;
  	}

  	//Reverese the direction
  	index_e = 8 - binary_size_e;
  	for (int i = 0; i < binary_size_e; i++) {
  		if(index_e > 0) {
  			exponent[i+index_e] = temp[binary_size_e - i - 1];
  		}
  		else {
  			exponent[i] = temp[binary_size_e - i - 1];
  		}
  	}
	}


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

  right_side[index + 1] = '\0';

  if (left_size == 0) {
    exponent_i = get_exponent_from_float(right_side, 1);

    // Create binary represenation for exponent
  	int index_e = 0, binary_size_e = 0;

    // Initialize buffers
  	while (index_e < 8) {
  		*(exponent + index_e) = '0';
  		*(temp + index_e) = '0';
  		index_e++;
  	}

  	index_e = 0;

  	// Store forward direction in temp.
  	while (exponent_i != 0 && index_e < 8) {
  		if ((exponent_i % 2) == 0) { // No remainder
  			*(temp + index_e) = '0';
  		}
  		else {
  			*(temp + index_e) = '1';
  		}
  		exponent_i /= 2;
  		index_e++;
  		binary_size_e++;
  	}

  	//Reverese the direction
  	index_e = 8 - binary_size_e;
  	for (int i = 0; i < binary_size_e; i++) {
  		if(index_e > 0) {
  			exponent[i+index_e] = temp[binary_size_e - i - 1];
  		}
  		else {
  			exponent[i] = temp[binary_size_e - i - 1];
  		}
  	}
	}

  /* ====                       =====*/
	/* ======= CREATE MANTISSA ========*/
	/* ====                       =====*/
	index = 0;

	// Add left side to mantissa
	for (int i = 1; i < left_size; i++) {
		if (index >= 23) {
			break;
		}
		else {
			mantissa_c[index] = left_side[i];
			index++;
		}
	}
	// Add right side to mantissa
	if (index != 0) {
		for (int i = 0; i < right_size; i++) {
			if (index >= 23) {
				break;
			}
			else {
				mantissa_c[index] = right_side[i];
				index++;
			}
		}
	}
	else {
		int found = 0;
		for (int i = 0; i < right_size; i++) {
			if (found) {
				if (index >= 23) {
					break;
				}
				else {
					mantissa_c[index] = right_side[i];
					index++;
				}
			}
			else {
				if (right_side[i] == '1') {
					found = 1;
				}
			}
		}
	}

  sign[1] = '\0';
  exponent[8] = '\0';
  mantissa_c[23] = '\0';

  return get_hex(sign, exponent, mantissa_c);
}
