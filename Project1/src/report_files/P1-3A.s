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
	.file	"P1-3A.c"
	.text
	.align	2
	.global	next_char
	.type	next_char, %function
next_char:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	sub	sp, sp, #12
	mov	r3, r0
	strb	r3, [fp, #-5]		// Get the parameter passed to the function
	ldrb	r3, [fp, #-5]
	add	r3, r3, #1		// Add 1 to the value
	uxtb	r3, r3			// Extend from 8-bit to 32 bit
	mov	r0, r3			// Move value to the return register 0
	sub	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
	.size	next_char, .-next_char
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Next Character= %c\012\000"	//Create ascii constant
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	mov	r0, #65			// Load in an initial value of 65 for 'A'
	bl	next_char		// Call next_char function
	mov	r3, r0
	ldr	r0, .L4
	mov	r1, r3
	bl	printf			// Print result using .LC0
	ldmfd	sp!, {fp, pc}
.L5:
	.align	2
.L4:
	.word	.LC0
	.size	main, .-main
	.ident	"GCC: (Raspbian 4.9.2-10+deb8u1) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
