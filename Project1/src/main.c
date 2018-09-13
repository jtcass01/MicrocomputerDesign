
#include <stdio.h>

signed int operand1;
signed int operand2;
signed int result;
signed int remainder;

signed int add(int operand_1, int operand_2);

void loop_menu(void);
void print_menu(void);
int is_operation(char);
void get_menu_response(char *, int *, int *);


int main(void) {
    loop_menu();
}

void loop_menu(void) {
    char response = '\0';

    while(response != 'q' && response != 'Q') {
        operand1 = 0;
        operand2 = 0;
        result = 0;
        remainder = 0;

        get_menu_response(&response, &operand1, &operand2);

        // Add
        if (response == 'a' || response == 'A') {

            printf("The summation of %d and %d is %d\n", operand1, operand2, add(operand1, operand2));

	// Subtract
        } else if (response == 's' || response == 'S') {

            printf("The difference between %d and %d is %d\n", operand1, operand2, result);

        // Multiply
        } else if (response == 'm' || response == 'M') {

            printf("The product of %d and %d is %d\n", operand1, operand2, result);

        // Divide
        } else if (response == 'd' || response == 'D') {

            printf("The quotient of %d and %d is %d with a remainder of %d\n", operand1, operand2, result, remainder);

        // Invalid response
        } else if (response != 'q' && response != 'Q') {
            printf("Invalid input to calculator.  Please try again.\n");
        }
    }
}

void print_menu(void) {
    printf("===== CALCULATOR MENU =====\n");
    printf("\ta) add\n");
    printf("\ts) subtract\n");
    printf("\tm) multiply\n");
    printf("\td) divide\n");
    printf("\tq) quit\n");
}

int is_operation(char response){
    if((response == 'a' || response == 'A') ||
       (response == 's' || response == 'S') ||
       (response == 'm' || response == 'M') ||
       (response == 'd' || response == 'D')) {
        return 1;
    } else {
        return 0;
    }
}

void get_menu_response(char *response, int *operand1, int *operand2) {
    print_menu();

    printf("\tResponse: ");
    scanf(" %c", response);

    if (is_operation(*response)) {
        printf("\tOperand 1: ");
        scanf(" %d", operand1);

        printf("\tOperand 2: ");
        scanf(" %d", operand2);
    }
}
