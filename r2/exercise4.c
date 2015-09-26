/*
 * Compile as gcc -g exercise4.c -o exercise4
 * Run as ./exercise4
 */

#include <stdio.h>

void printb(void *p);

int main(int argc, char **argv)
{
    int a = 42;
    float b = 13.37;

    printb(&a);
    printb(&b);

    return 0;
}

void printb(void *p)
{
    // solution that prints out leading 0s
    printf("0b");
    unsigned int *ptr = (unsigned int *)p;
    int i = 0;
    for (i = 31; i >= 0; i--)
    {
        printf("%x", (*ptr >> i) & 0x1);       
    }
    printf("\n");

    // solution that doesn't print out leading 0s
    printf("0b");
    int j = 0;
    for (i = 0; i < 32; i++)
    {
        unsigned int bit = (*ptr >> i) & 0x1;
        if (bit == 0x1)
            j = i;
    }
    for (i = j; i >= 0; i--)
    {
        printf("%x", (*ptr >> i) & 0x1);
    }
    printf("\n");
}
