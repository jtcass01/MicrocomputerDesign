//Assembly Subroutine
//Eugene Rockey, Copyright 2018, All Rights Reserved

.section ".text"
.global next_char

next_char:
    ADD r0,#1 //How is the ARM calling convention obeyed here?
    MOV pc,lr
    .end
