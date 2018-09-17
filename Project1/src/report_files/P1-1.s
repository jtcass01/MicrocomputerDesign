	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"P1-1.c"		// File Name
	.global	var1			// Create label to variable 1
	.data
	.type	var1, %object		// Set variable 1 type to object
	.size	var1, 1			// Size of variable 1 is 1 since char
var1:
	.byte	1			// Declare a byte of data
	.global	var2			// Create label to variable 2
	.type	var2, %object		// Set variable 2 type to object
	.size	var2, 1			// Size of variable 2 is 1 since char
var2:
	.byte	2			// Declare a byte of data
	.global	var3			// Create label to variable 3
	.align	2			// Moves address
	.type	var3, %object		// Sets variable 3 type to object
	.size	var3, 4			// Size of variable 3 is 4 since int
var3:
	.word	3			// Declare a word of data
	.global	var4			// Create label to variable 4
	.align	2			// Moves address
	.type	var4, %object		// Sets variable 4 type to object
	.size	var4, 4			// Size of variable 4 is 4 since int
var4:
	.word	4			// Declare a word of data
	.global	num			// Creates a label to variable num.
	.section	.rodata		// Moves section since constant
	.align	2			// Moves address
	.type	num, %object		// Sets num type to object
	.size	num, 4			// Size of num is 4 since int
num:
	.word	-10			// Declare a word of data
	.global	wave			// Creates a label to variable wave
	.data
	.align	2			// Moves address
	.type	wave, %object		// Sets wave type to object
	.size	wave, 10		// Size of wave is 10 since string is 10 char
wave:
	.ascii	"goodbye!!!"		// Declare an ascii string
	.global	__aeabi_idiv
	.text				// Signify the begining of code
	.align	2			// Moves address
	.global	main			// Creates label to main function
	.type	main, %function		// Sets type of main function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}		// Creates a "full descending stack" using the stack pointer and a return address.
	add	fp, sp, #4		// Adds 4 to the stack pointer and stores it in frame pointer.
	sub	sp, sp, #8		// Subtracts 8 from the stack pointer and stores in the stack pointer

	// SET VAR5 to 5
	mov	r3, #5			// Moves the constant 5 into register 3
	str	r3, [fp, #-8]           // Stores register 5's value.
	b	.L2                     // BEGINS THE FIRST FOR LOOP
.L3:    // INNER FOR LOOP
	ldr	r3, .L8			// Load register 3
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxtb	r2, r3			// Extends an 8 bit value to a 32 bit value
	ldr	r3, .L8
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxtb	r3, r3
	// VAR1 *= varaible 1
	smulbb	r3, r2, r3
	uxtb	r3, r3
	uxtb	r2, r3
	ldr	r3, .L8
	strb	r2, [r3]
	ldr	r3, .L8
	ldrb	r3, [r3]	@ zero_extendqisi2
	sxtb	r2, r3
	ldr	r3, .L8
	ldrb	r3, [r3]	@ zero_extendqisi2
	sxtb	r3, r3
	mov	r0, r2
	mov	r1, r3
	// VAR1 /= VAR1
	bl	__aeabi_idiv	
	mov	r3, r0
	uxtb	r2, r3
	ldr	r3, .L8
	strb	r2, [r3]
	ldr	r3, .L8
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxtb	r2, r3
	ldr	r3, .L8
	ldrb	r3, [r3]	@ zero_extendqisi2
	uxtb	r3, r3
	// VAR1 += VAR1
	add	r3, r2, r3
	uxtb	r3, r3
	uxtb	r2, r3
	ldr	r3, .L8
	strb	r2, [r3]
	ldr	r3, .L8
	mov	r2, #0
	strb	r2, [r3]
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1		// Decrement Variable 5
	str	r3, [fp, #-8]
.L2:	// FOR LOOP CONDITION
	ldr	r3, [fp, #-8]		// Load varaible 5 into register 3
	cmp	r3, #0			// Compare varaible 5 to zero.
	bgt	.L3			// If greater than, execute inner loop
.L4:    // DO WHILE LOOP
	ldr	r3, .L8+4		// Get variable 4
	ldr	r3, [r3]
	sub	r3, r3, #1		// Subtract 1 from variable 4
	ldr	r2, .L8+4
	str	r3, [r2]		// Store varaible 4
	ldr	r3, .L8+4
	ldr	r3, [r3]
	cmp	r3, #0			// See if while loop is true
	bne	.L4			// Repeat if not
	mov	r0, r0	@ nop
	// LAST WHILE LOOP
	ldr	r3, .L8+8
	ldr	r3, [r3]
	cmp	r3, #3			// Perform intiial comparison
	bne	.L1			// If equal, repeat
	ldr	r3, .L8+12
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L8+12
	strb	r2, [r3]
	mov	r0, r0	@ nop
.L1:
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L9:
	.align	2
.L8:
	.word	var1
	.word	var4
	.word	var3
	.word	var2
	.size	main, .-main
	.ident	"GCC: (Raspbian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
