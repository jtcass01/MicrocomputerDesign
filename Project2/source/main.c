// main.c - main for the CECS 525 Raspberry PI kernel
// by Eugene Rockey Copyright 2015 All Rights Reserved
// debug everything that needs debugging
// Add, remove, modify, preserve in order to fulfill project requirements.

#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "mmio.h"
#include "bcm2835.h"
#include "can.h"
#include "softfloat.h"
#include "math.h"

const char MS1[] = "\r\n\nCECS-525 RPI Tiny OS";
const char MS2[] = "\r\nby Eugene Rockey Copyright 2013 All Rights Reserved";
const char MS3[] = "\r\nReady: ";
const char MS4[] = "\r\nInvalid Command Try Again...";

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

//Pointers to some of the BCM2835 peripheral register bases
volatile uint32_t* bcm2835_gpio = (uint32_t*)BCM2835_GPIO_BASE;
volatile uint32_t* bcm2835_clk = (uint32_t*)BCM2835_CLOCK_BASE;
volatile uint32_t* bcm2835_pads = (uint32_t*)BCM2835_GPIO_PADS;//for later updates to program
volatile uint32_t* bcm2835_spi0 = (uint32_t*)BCM2835_SPI0_BASE;
volatile uint32_t* bcm2835_bsc0 = (uint32_t*)BCM2835_BSC0_BASE;//for later updates to program
volatile uint32_t* bcm2835_bsc1 = (uint32_t*)BCM2835_BSC1_BASE;
volatile uint32_t* bcm2835_st = (uint32_t*)BCM2835_ST_BASE;

uint8_t response = '\0';
uint8_t num_1 = '\0';
int number1 = 0;
uint8_t num_2 = '\0';
int number2 = 0;
int result = 0;
int div_remainder = 0;
uint8_t result_response = '\0';

void testdelay(void)
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
        while(response == '\0'){;}
}


void get_numbers(void) {
	uart_puts("\r\nNumber 1: ");
        wait_for_response();
        num_1 = response;
	number1 = (int) num_1;

	uart_puts("\r\nNumber 2: ");
	wait_for_response();
	num_2 = response;
	number2 = (int) num_2;

	uart_puts("\r\nNumber 1: ");
	uart_putc(num_1);

	uart_puts("\r\nNumber 2: ");
	uart_putc(num_2);
}

void ADD(void) {
	get_numbers();
	result = add(number1, number2);
	result_response = (uint8_t) result;
	uart_puts("\r\nADD");
	uart_putc(result_response);
}

void SUBTRACT(void)
{
	get_numbers();
	result = subtract(number1, number2);
	result_response = (uint8_t) result;
	uart_puts("\r\nSUBTRACT");
	uart_putc(result_response);
}

void DIVIDE(void)
{
	get_numbers();
	uart_puts("\r\nDIVIDE");
}

void MULTIPLY(void)
{
	get_numbers();
	uart_puts("\r\nMULTIPLY");
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

