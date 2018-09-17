//Eugene Rockey, Copyright 2018, All rights reserved.
//Project 1 Part 3A
//Compile on Raspberry PI using the command 'gcc P1-3A.c' to make sure no errors exist.
//Run and test the program by entering './a.out'
//Generate the Assembly listing by entering ‘gcc -S P1-3A.c’
//Open the generated Assembly file ‘P1-3A.s’ and fulfill part 3A requirements.

#include <stdio.h>

unsigned char next_char(char in) {
    return in + 1;
}

void main() {
    printf("Next Character= %c\n",next_char('A'));
}

