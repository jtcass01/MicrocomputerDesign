#include <stdio.h>

void function(int, int, int *, int *);

void main(void) {
    int quotient = -15, divisor = -4, result = 1, remainder = 9;

    function(quotient, divisor, &result, &remainder);

    printf("%d %d %d %d", quotient, divisor, result, remainder);
}


void function(int quotient, int divisor, int *result, int *remainder){
    int result_value = *result, remainder_value = *remainder, flip_res = 0, flip_remain = 0;
    result_value = 0;
    remainder_value = 0;

    if(quotient < 0 && divisor > 0) {
        quotient *= -1;
        flip_res = 1;
        flip_remain = 1;
    } else if (quotient > 0 && divisor < 0) {
        divisor *= -1;
        flip_res = 1;
    } else if (quotient < 0 && divisor < 0) {
        quotient *= -1;
        divisor *= -1;
        flip_remain = 1;
    }

compare:
    if(quotient > 0) {
       goto reduce;
    } else {
       goto return_values;
    }

reduce:
    quotient -= divisor;
    if(quotient >= 0) {
        result_value += 1;
    }
    goto compare;

return_values:
    if(quotient != 0){
        remainder_value = quotient + divisor;
    }

    if(flip_res) {
        result_value *= -1;
    }

    if(flip_remain) {
        remainder_value *= -1;
    }

    *result = result_value;
    *remainder = remainder_value;
}
