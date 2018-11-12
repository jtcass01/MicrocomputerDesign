// main.c - main for the CECS 525 Raspberry PI kernel
// by Eugene Rockey Copyright 2015 All Rights Reserved
// debug everything that needs debugging
// Add, remove, modify, preserve in order to fulfill project requirements.

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"
#include "mmio.h"
#include "bcm2835.h"
#include "can.h"
#include "softfloat.h"
#include "math.h"
#include "converter.h"

const char MS1[] = "\r\n\nCECS-525 RPI Tiny OS";
const char MS2[] = "\r\nby Eugene Rockey Copyright 2013 All Rights Reserved";
const char MS3[] = "\r\nReady: ";
const char MS4[] = "\r\nInvalid input to calculator.  Please try again.";

void kernel_main();             //prototypes
void enable_arm_irq();
void disable_arm_irq();
void enable_arm_fiq();
void disable_arm_fiq();
void reboot();
void enable_irq_57();
void disable_irq_57();
void testdelay();
extern int invar;               //assembly variables
extern int outvar;

uint32_t vfp11_add(uint32_t operand_1, uint32_t operand_2);
uint32_t vfp11_sub(uint32_t operand_1, uint32_t operand_2);
uint32_t vfp11_mult(uint32_t operand_1, uint32_t operand_2);
uint32_t vfp11_div(uint32_t operand_1, uint32_t operand_2);

//Pointers to some of the BCM2835 peripheral register bases
volatile uint32_t* bcm2835_gpio = (uint32_t*)BCM2835_GPIO_BASE;
volatile uint32_t* bcm2835_clk = (uint32_t*)BCM2835_CLOCK_BASE;
volatile uint32_t* bcm2835_pads = (uint32_t*)BCM2835_GPIO_PADS;//for later updates to program
volatile uint32_t* bcm2835_spi0 = (uint32_t*)BCM2835_SPI0_BASE;
volatile uint32_t* bcm2835_bsc0 = (uint32_t*)BCM2835_BSC0_BASE;//for later updates to program
volatile uint32_t* bcm2835_bsc1 = (uint32_t*)BCM2835_BSC1_BASE;
volatile uint32_t* bcm2835_st = (uint32_t*)BCM2835_ST_BASE;

uint8_t response = '\0';
uint8_t result_response[32];
float num1_f = 0;
float num2_f = 0;
float result = 0;

void testdelay(void)
{
	int count = 0xFFFFF;
	while (count > 0) {count = count - 1;}
}

void multi_char_delay(void)
{
	int count = 0xFFFFF;
	while (count > 0) {count = count - 1;}
}

void enable_irq_57(void)
{
	mmio_write(0x2000B214, 0x02000000);
}

void disable_irq_57(void)
{
	mmio_write(0x2000B220, 0x02000000);
}

void banner(void)
{
	uart_puts(MS1);
	uart_puts(MS2);
}

uint8_t BCDtoUint8(uint8_t BCD)
{
	return (BCD & 0x0F) + ((BCD >> 4) * 10);
}

void RES(void)
{
	reboot();
}

void MENU(void) //Command List
{
	uart_puts("\r\n\n(A)dd,(S)ubtract,(D)ivide,(M)ultiply");
}

void wait_for_response(void)
{
        response = '\0';
        while(response == '\0'){}
}

int char_to_int(uint8_t character)
{
	return character - '0';
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    itoa(ipart, res);

    //find size of int
    int int_size = 0;
    for(int i = 0; *(i + res) != '\0'; i++) {
      int_size++;
    }

    // check for display option after point
    if (afterpoint != 0)
    {
        res[int_size] = '.';  // add dot

        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        for(int i = 0; i < afterpoint; i++){
          fpart *= 10;
        }

        itoa((int)fpart, res + int_size + 1);
    }
}


float get_number(void){
  int negative= 0;
	float number = 0.0;

  wait_for_response();

	while(response != '.') {
		if(response == '-') {
			negative = 1;
		} else {
	    number = (number*10) + char_to_int(response);
		}
	  wait_for_response();
	}

	while(response != ';') {
		number = (number*10) + char_to_int(response);
	  wait_for_response();
  }

	if (negative) {
	    return number*-1;
	} else {
	    return number;
	}

}

void get_numbers(void) {
	uart_puts("\r\nNumber 1: ");
	num1_f = get_number();

	uart_puts("\r\nNumber 2: ");
	num2_f = get_number();
}

void ADD(void) {
	get_numbers();
	SinglePrecisionFloat *operand_1 = create_single_precision_float_from_float(num1_f);
	SinglePrecisionFloat *operand_2 = create_single_precision_float_from_float(num2_f);
	SinglePrecisionFloat *result;

	result = create_single_precision_float_from_hex(vfp11_add(operand_1->hex, operand_2->hex));

	uart_puts("\r\nThe sum of ");
	ftoa(operand_1->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" and ");
	ftoa(operand_2->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" is ");
	ftoa(result->o, result_response, 4);
	uart_puts(result_response);

	delete_single_precision_float(operand_1);
	delete_single_precision_float(operand_2);
	delete_single_precision_float(result);
}

void SUBTRACT(void)
{
	get_numbers();
	SinglePrecisionFloat *operand_1 = create_single_precision_float_from_float(num1_f);
	SinglePrecisionFloat *operand_2 = create_single_precision_float_from_float(num2_f);
	SinglePrecisionFloat *result;

	result = create_single_precision_float_from_hex(vfp11_sub(operand_1->hex, operand_2->hex));

	uart_puts("\r\nThe difference of ");
	ftoa(operand_1->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" and ");
	ftoa(operand_2->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" is ");
	ftoa(result->o, result_response, 4);
	uart_puts(result_response);

	delete_single_precision_float(operand_1);
	delete_single_precision_float(operand_2);
	delete_single_precision_float(result);
}

void DIVIDE(void)
{
	get_numbers();
	SinglePrecisionFloat *operand_1 = create_single_precision_float_from_float(num1_f);
	SinglePrecisionFloat *operand_2 = create_single_precision_float_from_float(num2_f);
	SinglePrecisionFloat *result;

	result = create_single_precision_float_from_hex(vfp11_div(operand_1->hex, operand_2->hex));

	uart_puts("\r\nThe quotient of ");
	ftoa(operand_1->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" and ");
	ftoa(operand_2->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" is ");
	ftoa(result->o, result_response, 4);
	uart_puts(result_response);

	delete_single_precision_float(operand_1);
	delete_single_precision_float(operand_2);
	delete_single_precision_float(result);
}

void MULTIPLY(void)
{
	get_numbers();
	SinglePrecisionFloat *operand_1 = create_single_precision_float_from_float(num1_f);
	SinglePrecisionFloat *operand_2 = create_single_precision_float_from_float(num2_f);
	SinglePrecisionFloat *result;

	result = create_single_precision_float_from_hex(vfp11_mult(operand_1->hex, operand_2->hex));

	uart_puts("\r\nThe product of ");
	ftoa(operand_1->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" and ");
	ftoa(operand_2->o, result_response, 4);
	uart_puts(result_response);

	uart_puts(" is ");
	ftoa(result->o, result_response, 4);
	uart_puts(result_response);

	delete_single_precision_float(operand_1);
	delete_single_precision_float(operand_2);
	delete_single_precision_float(result);
}

void VOLUME(void)
{
	get_number();
	SinglePrecisionFloat *radiusnum = create_single_precision_float_from_float(num1_f);
	SinglePrecisionFloat *fourthird = create_single_precision_float_from_hex(0x3FAAAAAB);
	SinglePrecisionFloat *pi = create_single_precision_float_from_hex(0x40490FDB);
	SinglePrecisionFloat *result = create_single_precision_float_from_hex(vfp11_mult(vfp11_mult(vfp11_mult(vfp11_mult(fourthird->hex, pi->hex), radiusnum->hex), radiusnum->hex), radiusnum->hex));
	
	uart_puts("\r\nThe Volume of a Sphere with Radius: ");
	uart_puts(result_response);
	ftoa(radiusnum->o, result_response, 4);
	
	uart_puts(" is ");
	ftoa(result->o, result_response, 4);
	
	delete_single_precision_float(radiusnum);
	delete_single_precision_float(fourthird);
	delete_single_precision_float(pi);
	delete_single_precision_float(result);
}



void command(void)
{
	uart_puts(MS3);
        wait_for_response();

	switch (response) {
		case 'A' | 'a':
			ADD();
			break;
		case 'S' | 's':
			SUBTRACT();
			break;
		case 'D' | 'd':
			DIVIDE();
			break;
		case 'M' | 'm':
			MULTIPLY();
			break;
		case 'V' | 'v' :
			VOLUME();
			break;
		default:
			uart_puts(MS4);
			break;
	}
	MENU();
}

void kernel_main()
{
	uart_init();
	enable_irq_57();
	enable_arm_irq();

	banner();
	MENU();
	while (1) {command();}

}


void irq_handler(void)
{
    response = uart_readc();

    uart_putc(' ');
    uart_putc(response);
    uart_putc(' ');
}
