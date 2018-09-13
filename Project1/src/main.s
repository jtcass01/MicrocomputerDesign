//Assembly

    .section ".text"
    
    .global add
    .global subtract
    .global multiply
    .global divide

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
    ADD    r0, r0, r1
    MOV    pc, lr

