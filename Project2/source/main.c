// main.c - main for the CECS 525 Raspberry PI kernel
// by Eugene Rockey Copyright 2015 All Rights Reserved
// debug everything that needs debugging
// Add, remove, modify, preserve in order to fulfill project requirements.

#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "mmio.h"
#include "bcm2835.h"
#include "can.h"
#include "softfloat.h"
#include "math.h"

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

signed int add(int operand_1, int operand_2);
signed int subtract(int operand_1, int operand_2);
signed int multiply(int operand_1, int operand_2);
signed int divide_2(int operand_1, int operand_2, int *result, int *remainder);

//Pointers to some of the BCM2835 peripheral register bases
volatile uint32_t* bcm2835_gpio = (uint32_t*)BCM2835_GPIO_BASE;
volatile uint32_t* bcm2835_clk = (uint32_t*)BCM2835_CLOCK_BASE;
volatile uint32_t* bcm2835_pads = (uint32_t*)BCM2835_GPIO_PADS;//for later updates to program
volatile uint32_t* bcm2835_spi0 = (uint32_t*)BCM2835_SPI0_BASE;
volatile uint32_t* bcm2835_bsc0 = (uint32_t*)BCM2835_BSC0_BASE;//for later updates to program
volatile uint32_t* bcm2835_bsc1 = (uint32_t*)BCM2835_BSC1_BASE;
volatile uint32_t* bcm2835_st = (uint32_t*)BCM2835_ST_BASE;

uint8_t response = '\0';
uint8_t response_buffer[20];
int buffer_position = 0;

uint8_t num1_c = '\0';
int num1_i = 0;
uint8_t num2_c = '\0';
int num2_i = 0;
int result = 0;
int div_remainder = 0;
char result_response[20];

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
	uart_puts("\r\n(A)dd,(S)ubtract,(D)ivide,(M)ultiply");
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

int get_number(void){
    int number = 0;

    wait_for_response();
    while(response != '.') {
        number = (number*10) + char_to_int(response);
        wait_for_response();
    }

    return number;
}

void get_numbers(void) {
	uart_puts("\r\nNumber 1: ");
	num1_i = get_number();

	uart_puts("\r\nNumber 2: ");
	num2_i = get_number();
}

void ADD(void) {
	get_numbers();
	result = add(num1_i, num2_i);

	uart_puts("\r\nThe sum of ");
	itoa(num1_i, result_response);
	uart_puts(result_response);

	uart_puts(" and ");
	itoa(num2_i, result_response);
	uart_puts(result_response);

	uart_puts(" is ");
	itoa(result, result_response);
	uart_puts(result_response);
}

void SUBTRACT(void)
{
	get_numbers();
	result = subtract(num1_i, num2_i);

	uart_puts("\r\nThe difference of ");
	itoa(num1_i, result_response);
	uart_puts(result_response);

	uart_puts(" and ");
	itoa(num2_i, result_response);
	uart_puts(result_response);

	uart_puts(" is ");
	itoa(result, result_response);
	uart_puts(result_response);
}

void DIVIDE(void)
{
	get_numbers();
	uart_puts("\r\nDIVIDE");
}

void MULTIPLY(void)
{
	get_numbers();
	result = multiply(num1_i, num2_i);

	uart_puts("\r\nThe product of ");
	itoa(num1_i, result_response);
	uart_puts(result_response);

	uart_puts(" and ");
	itoa(num2_i, result_response);
	uart_puts(result_response);

	uart_puts(" is ");
	itoa(result, result_response);
	uart_puts(result_response);
}

void command(void)
{
	uart_puts(MS3);
        wait_for_response();
	response_buffer[buffer_position] = '\0';

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

