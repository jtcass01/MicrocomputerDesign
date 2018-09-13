//Assembly
    .text
    .global add
    .global subtract
    .global multiply
    .global divide
    .global divide_2

add:
    ADD    r0, r0, r1
    MOV    pc, lr

subtract:
    SUB    r0, r0, r1
    MOV    pc, lr

multiply:
    MUL    r0, r0, r1
    MOV    pc, lr


divide:
    // r4 is the Result
    LDR   r4, [r2]
    // r5 is the Remainder
    LDR   r5, [r3]
    //r0 is divisor
    MOV   r6, r0
    //r1 is quotient

compairson:
    // Check if divisor > 0
    CMP    r0, #0
    BGT    reduce
    BEQ    return_zero

    ADD    r3, r0, r1

return_values:
    // Store Result
    STR    r4, [r2]
    // Store remainder
    STR    r5, [r3]
    MOV    pc, lr

reduce:
    SUB    r0, r0, r1
    ADD    r4, r4, #1
    BAL    compairson

return_zero:
    MOV    r4, #0
    MOV    r5, #0
    BAL    return_values

divide_2:
        str     fp, [sp, #-4]!
        add     fp, sp, #0
        sub     sp, sp, #36
        str     r0, [fp, #-24]
        str     r1, [fp, #-28]
        str     r2, [fp, #-32]
        str     r3, [fp, #-36]
        ldr     r3, [fp, #-32]
        ldr     r3, [r3]
        str     r3, [fp, #-8]
        ldr     r3, [fp, #-36]
        ldr     r3, [r3]
        str     r3, [fp, #-12]
        mov     r3, #0
        str     r3, [fp, #-16]
        mov     r3, #0
        str     r3, [fp, #-20]
        mov     r3, #0
        str     r3, [fp, #-8]
        mov     r3, #0
        str     r3, [fp, #-12]
        ldr     r3, [fp, #-24]
        cmp     r3, #0
        bge     .L5
        ldr     r3, [fp, #-28]
        cmp     r3, #0
        ble     .L5
        ldr     r3, [fp, #-24]
        rsb     r3, r3, #0
        str     r3, [fp, #-24]
        mov     r3, #1
        str     r3, [fp, #-16]
        mov     r3, #1
        str     r3, [fp, #-20]
        b       .L6
.L5:
        ldr     r3, [fp, #-24]
        cmp     r3, #0
        ble     .L7
        ldr     r3, [fp, #-28]
        cmp     r3, #0
        bge     .L7
        ldr     r3, [fp, #-28]
        rsb     r3, r3, #0
        str     r3, [fp, #-28]
        mov     r3, #1
        str     r3, [fp, #-16]
        b       .L6
.L7:
        ldr     r3, [fp, #-24]
        cmp     r3, #0
        bge     .L6
        ldr     r3, [fp, #-28]
        cmp     r3, #0
        bge     .L6
        ldr     r3, [fp, #-24]
        rsb     r3, r3, #0
        str     r3, [fp, #-24]
        ldr     r3, [fp, #-28]
        rsb     r3, r3, #0
        str     r3, [fp, #-28]
        mov     r3, #1
        str     r3, [fp, #-20]
.L6:
        ldr     r3, [fp, #-24]
        cmp     r3, #0
        ble     .L8
        mov     r0, r0  @ nop
.L9:
        ldr     r2, [fp, #-24]
        ldr     r3, [fp, #-28]
        rsb     r3, r3, r2
        str     r3, [fp, #-24]
        ldr     r3, [fp, #-24]
        cmp     r3, #0
        blt     .L11
        b       .L15
.L8:
        mov     r0, r0  @ nop
.L10:
        ldr     r3, [fp, #-24]
        cmp     r3, #0
        beq     .L12
        b       .L16
.L15:
        ldr     r3, [fp, #-8]
        add     r3, r3, #1
        str     r3, [fp, #-8]
.L11:
        b       .L6
.L16:
        ldr     r2, [fp, #-24]
        ldr     r3, [fp, #-28]
        add     r3, r2, r3
        str     r3, [fp, #-12]
.L12:
        ldr     r3, [fp, #-16]
        cmp     r3, #0
        beq     .L13
        ldr     r3, [fp, #-8]
        rsb     r3, r3, #0
        str     r3, [fp, #-8]
.L13:
        ldr     r3, [fp, #-20]
        cmp     r3, #0
        beq     .L14
        ldr     r3, [fp, #-12]
        rsb     r3, r3, #0
        str     r3, [fp, #-12]
.L14:
        ldr     r3, [fp, #-32]
        ldr     r2, [fp, #-8]
        str     r2, [r3]
        ldr     r3, [fp, #-36]
        ldr     r2, [fp, #-12]
        str     r2, [r3]
        sub     sp, fp, #0
        ldr     fp, [sp], #4
        bx      lr
