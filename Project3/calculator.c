#include "headers/calculator.h"

void prompt_convert_number(void) {
  float classic_float;
  SinglePrecisionFloat *spf_float;

  printf("Enter a number to convert from float to binary: ");
  scanf("%f", &classic_float);

  spf_float = create_single_precision_float(classic_float);
  delete_single_precision_float(spf_float);
}

int menu(void) {
  int response = 0;

  printf("=== Calculator Menu ====\n");
  printf("1) test conversion\n");
  printf("0) quit\n");
  scanf("%d", &response);

  return response;
}

int main()
{
  int response = 1;

  while(response != 0) {
    response = menu()

    switch(response) {
      case 1:
        prompt_convert_number();
        break;
    }
  }

  return 0;
} // end main
