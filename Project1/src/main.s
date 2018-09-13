//Assembly

    .section ".text"
    
    .global add

add:
    ADD    r0, r0, r1
    MOV    pc, lr
