#include "headers/calculator.h"

void prompt_convert_number(void) {
  float classic_float;
  SinglePrecisionFloat *spf_float;

  printf("Enter a number to convert from float to binary: ");
  scanf("%f", &classic_float);

  spf_float = create_single_precision_float_from_float(classic_float);
  printf("%f represented as hex is %X\n", spf_float->o, spf_float->hex);
  uint32_t hex_value = spf_float->hex;
  delete_single_precision_float(spf_float);

  spf_float = create_single_precision_float_from_hex(hex_value);
  printf("%X represented as float is %f\n", spf_float->hex, spf_float->o);
  delete_single_precision_float(spf_float);
}

void prompt_add(void) {
  float classic_float = 0.0;
  uint32_t hex_result = 0x0;
  SinglePrecisionFloat *num1, *num2, *result;

  printf("Enter a the first number:");
  scanf("%f", &classic_float);
  num1 = create_single_precision_float_from_float(classic_float);

  printf("Enter a the second number:");
  scanf("%f", &classic_float);
  num2 = create_single_precision_float_from_float(classic_float);

  hex_result = add(num1->hex, num2->hex);

  result = create_single_precision_float_from_hex(hex_result);
  printf(" %f + %f = %f\n", num1->o, num2->o, result->o);

  delete_single_precision_float(num1);
  delete_single_precision_float(num2);
  delete_single_precision_float(result);
}

void prompt_subtract(void) {
  float classic_float = 0.0;
  uint32_t hex_result = 0x0;
  SinglePrecisionFloat *num1, *num2, *result;

  printf("Enter a the first number:");
  scanf("%f", &classic_float);
  num1 = create_single_precision_float_from_float(classic_float);

  printf("Enter a the second number:");
  scanf("%f", &classic_float);
  num2 = create_single_precision_float_from_float(classic_float);

  hex_result = subtract(num1->hex, num2->hex);

  result = create_single_precision_float_from_hex(hex_result);
  printf(" %f - %f = %f\n", num1->o, num2->o, result->o);

  delete_single_precision_float(num1);
  delete_single_precision_float(num2);
  delete_single_precision_float(result);
}


void prompt_multiply(void) {
  float classic_float = 0.0;
  uint32_t hex_result = 0x0;
  SinglePrecisionFloat *num1, *num2, *result;

  printf("Enter a the first number:");
  scanf("%f", &classic_float);
  num1 = create_single_precision_float_from_float(classic_float);

  printf("Enter a the second number:");
  scanf("%f", &classic_float);
  num2 = create_single_precision_float_from_float(classic_float);

  hex_result = multiply(num1->hex, num2->hex);

  result = create_single_precision_float_from_hex(hex_result);
  printf(" %f * %f = %f\n", num1->o, num2->o, result->o);

  delete_single_precision_float(num1);
  delete_single_precision_float(num2);
  delete_single_precision_float(result);
}


void prompt_divide(void) {
  float classic_float = 0.0;
  uint32_t hex_result = 0x0;
  SinglePrecisionFloat *num1, *num2, *result;

  printf("Enter a the first number:");
  scanf("%f", &classic_float);
  num1 = create_single_precision_float_from_float(classic_float);

  printf("Enter a the second number:");
  scanf("%f", &classic_float);
  num2 = create_single_precision_float_from_float(classic_float);

  hex_result = divide(num1->hex, num2->hex);

  result = create_single_precision_float_from_hex(hex_result);
  printf(" %f / %f = %f\n", num1->o, num2->o, result->o);

  delete_single_precision_float(num1);
  delete_single_precision_float(num2);
  delete_single_precision_float(result);
}


void prompt_volume(void) {
  float classic_float = 0.0;
  uint32_t hex_result = 0x0;
  SinglePrecisionFloat *radius, *four_third, *pi, *result;

  printf("Enter the radius of the sphere:");
  scanf("%f", &classic_float);
  radius = create_single_precision_float_from_float(classic_float);
  four_third = create_single_precision_float_from_float((float) 4 / (float) 3);
  pi = create_single_precision_float_from_float(3.14159);

  // r ^ 3
  hex_result = multiply(multiply(radius->hex, radius->hex), radius->hex);
  // r ^ 3 * pi
  hex_result = multiply(hex_result, pi->hex);
  // r ^ 3 * pi * (3/4)
  hex_result = multiply(hex_result, four_third->hex);

  result = create_single_precision_float_from_hex(hex_result);
  printf("The volume of a sphere with radius %f is %f\n", radius->o, result->o);

  delete_single_precision_float(radius);
  delete_single_precision_float(four_third);
  delete_single_precision_float(pi);
  delete_single_precision_float(result);
}

uint32_t add(uint32_t op1, uint32_t op2) {
  return 0x0;
}

uint32_t subtract(uint32_t op1, uint32_t op2) {
  return 0x0;
}

uint32_t multiply(uint32_t op1, uint32_t op2) {
  return 0x0;
}

uint32_t divide(uint32_t op1, uint32_t op2) {
  return 0x0;
}


int menu(void) {
  int response = 0;

  printf("=== Calculator Menu ====\n");
  printf("1) test conversion\n");
  printf("2) Add\n");
  printf("3) Subtract\n");
  printf("4) Multiply\n");
  printf("5) Divide\n");
  printf("6) Volume of sphere\n");
  printf("0) quit\n");
  scanf("%d", &response);

  return response;
}

int main()
{
  int response = 1;

  while(response != 0) {
    response = menu();

    switch(response) {
      case 1:
        prompt_convert_number();
        break;
      case 2:
        prompt_add();
        break;
      case 3:
        prompt_subtract();
        break;
      case 4:
        prompt_multiply();
        break;
      case 5:
        prompt_divide();
        break;
      case 6:
        prompt_volume();
        break;
    }
  }

  return 0;
} // end main
