// main.c - main for the CECS 525 Raspberry PI kernel
// by Eugene Rockey Copyright 2015 All Rights Reserved
// debug everything that needs debugging
// Add, remove, modify, preserve in order to fulfill project requirements.

#include <stdint.h>
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



//Pointers to some of the BCM2835 peripheral register bases
volatile uint32_t* bcm2835_gpio = (uint32_t*)BCM2835_GPIO_BASE;
volatile uint32_t* bcm2835_clk = (uint32_t*)BCM2835_CLOCK_BASE;
volatile uint32_t* bcm2835_pads = (uint32_t*)BCM2835_GPIO_PADS;//for later updates to program
volatile uint32_t* bcm2835_spi0 = (uint32_t*)BCM2835_SPI0_BASE;
volatile uint32_t* bcm2835_bsc0 = (uint32_t*)BCM2835_BSC0_BASE;//for later updates to program
volatile uint32_t* bcm2835_bsc1 = (uint32_t*)BCM2835_BSC1_BASE;
volatile uint32_t* bcm2835_st = (uint32_t*)BCM2835_ST_BASE;

uint8_t response = '\0';

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

void ADD(void)
{
	uart_puts("\r\nADD");
}

void SUBTRACT(void)
{
	uart_puts("\r\nSUBTRACT");
}

void DIVIDE(void)
{
	uart_puts("\r\nDIVIDE");
}

void MULTIPLY(void)
{
	uart_puts("\r\nMULTIPLY");
}

void command(void)
{
	uart_puts(MS3);
        response = '\0';
	while (response == '\0') {
	}
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

    switch(response) {
        case 'A' | 'a':
            ADD();
            break;
        default:
            uart_puts(MS4);
            break;
    }

    uart_putc(' ');
    uart_putc(response);
    uart_putc(' ');
}

