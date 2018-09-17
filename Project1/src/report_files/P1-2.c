//Eugene Rockey, Copyright 2018, All rights reserved.
//Project 1 Part 2
//Compile on Raspberry PI using the command ‘gcc P1-2.c’ to make sure there are no errors.
//Compile on Raspberry PI using the command 'gcc -S P1-2.c' to generate Assembly listing.
//Open the generated Assembly file P1-2.s and fulfill part 2 requirements.

//volatile modifier for variables that chage due to hardware interrupts, RTC, etc... 
volatile int var;

//Function with Pointers
void swap(int *x, int *y) {
    int temp; temp = *x; *x = *y; *y = temp;
}

//A stack frame (fp) is used here for the subroutine(function) call.
//Also, the stack is used when switching between OS and main() too. 

int main() {
    //local variables
    int a, b;
    a = 10;
    b = 20;
    swap(&a, &b);
    return 0;
}
