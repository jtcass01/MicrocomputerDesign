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

  printf("Binary (sign bit, 8-bit biased exponent, 23-bit fraction): %s", floatToBinary(num.piece.sign, 1));
  printf("%s", floatToBinary(num.piece.exponent, 8));
  printf("%s", floatToBinary(num.piece.mantissa, 23));
  printf("\nHexadecimal: 0x%X", binaryToHex());

  return 0;
} // end main

#ifdef old
/**
 * convert float to binary representation
 */
void floatToBinary(float num)
{
  printf("%f to binary: \n", num);
  int binarynum[1000], binarydec[1000];
  int i = 0, k = 0;
  int temp = (int)num;
  float dec = num - temp;

  printf("Integer: %d\n", temp); // print left of decimal point
  printf("Fraction: %f\n", dec); // print right of decimal point

  while (temp > 0)
  {
    binarynum[i] = temp % 2;
    temp = temp / 2;
    i++;
  }

  printf("Binary: ");
  for (int j = i - 1; j >= 0; j--)
    printf("%d", binarynum[j]);
  printf("."); // display the decimal point in binary output

  while (k < 23)
  {
    dec = dec * 2.0;

    if ((int)dec == 0)
      binarydec[k] = 0;

    if ((int)dec == 1)
    {
      binarydec[k] = 1;
      dec -= 1; // greater than one so subtract one
    }

    k++;
  }

  for (int l = 0; l < k; l++)
    printf("%d", binarydec[l]);
} // end floatToBinary

void main()
{
  float num;
  printf("Enter: ");
  scanf("%f", &num);
  binary(num, 32);
}

#endif