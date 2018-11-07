#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char exponent[8];
char mantissa[23];
char binary[32]; // sign bit + exponent + mantissa
char hex[100];

/**
 * binary represention of float structure
 */
typedef union {
  float f;
  struct
  {
    unsigned int mantissa : 23; // 23-bit fraction
    unsigned int exponent : 8;  // 8-bit biased exponent
    unsigned int sign : 1;      // 1-bit sign
  } piece;
} myFloat; // end

/**
 * convert various pieces of float to binary
 * including fraction (23-bit) and exponent (8-bit)
 */
char *floatToBinary(int n, int i)
{
  int k, j;
  int piece = i;

  for (j = 0, i--; i >= 0; j++, i--)
  {
    k = n >> i; // k equals n logical shift right
    if (k & 1)  // if k AND 1 is true
      ((piece == 23) ? (mantissa[j] = '1') : (exponent[j] = '1'));
    else
      ((piece == 23) ? (mantissa[j] = '0') : (exponent[j] = '0'));
  }

  return ((piece == 23) ? mantissa : exponent);
} // end floatToBinary

/**
 * convert binary string to hex
 */
int binaryToHex()
{
  char *a = exponent;
  int hexNum = 0;
  do
  {
    if()
    int b = *a == '1' ? 1 : 0;
    hexNum = ((hexNum << 1) | b);
    a++;
  } while (*a);

  return hexNum;
} // end binaryToHex

/**
 * driver function
 */
int main()
{
  myFloat num;
  printf("Enter: ");
  scanf("%f", &num.f);

  printf("Sign: %s\n", floatToBinary(num.piece.sign, 1));
  printf("Exponent: %s\n", floatToBinary(num.piece.exponent, 8));
  printf("Mantissa: %s\n", floatToBinary(num.piece.mantissa, 23));
  printf("\nHexadecimal: 0x%X\n", binaryToHex());

  return 0;
} // end main
