/*
 * Compile as gcc -g exercise1.c -o exercise1
 * Run as ./exercise1
 */

#include <stdio.h>

int main(int argc, char **argv)
{
    int a = 86;
    int b = -94;
    int c = a + b;
    // let's examine our memory in GDB
    // b exercise1.c:18 to break right before the print statement
    // p <var> to view the variable
    // p /x <var> to view the variable in hexadecimal
    // x/4xb &<var> to view 4 bytes memory in hexadecimal at the address of the variable
    printf("a:0x%08x\nb:0x%08x\nc:0x%08x\n", a, b, c);
}
