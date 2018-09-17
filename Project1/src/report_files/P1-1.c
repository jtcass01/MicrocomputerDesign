//Eugene Rockey, Copyright 2018, All rights reserved. //Project 1 Part 1 //Compile on Raspberry PI using the command ‘gcc P1-1.c’ to make sure there are no errors. //Compile on Raspberry PI using the command 'gcc -S P1-1.c' to generate Assembly listing. //Open the generated Assembly file named P1-1.s and fulfill part 1 requirements.
//Global Data Types
signed char var1 = 1;
unsigned char var2 = 2;
signed int var3 = 3;
unsigned int var4 = 4;
const int num = -10;
char wave[10]="goodbye!!!";

void main() {
    //Local Data Type
    int var5 = 5;

    //Various Loop Types
    for (var5;var5>0;var5--) {
        var1*=var1; var1/=var1; var1+=var1; var1-=var1;
    }


    do {
        var4-=1;
    }   while(var4>0);


    while(var3 == 3) {
        var2 = var2;
        break;
    }
}
