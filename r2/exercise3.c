/*
 * Compile as gcc -g exercise3.c -o exercise3
 * Run as ./exercise3
 */

#include <stdio.h>

int main(int argc, char **argv)
{
    float a = 64.0;
    int b = 1073741825; // = 2^30 + 1
    a *= -1.0;
    
    // a += b;
    // the compiler won't get confused and misinterpret a to be an integer
    // so we must force the compiler to create a new variable that takes
    // the values stored in memory at &a and interpret that as an integer
    int *a_misinterpreted = (int *)&a;
    *a_misinterpreted += b;

    printf("-a + b = %.40f\n", a);
}
