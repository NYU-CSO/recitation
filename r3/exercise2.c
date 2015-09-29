/*
 * Compile as gcc -g exercise2.c -o exercise2
 * Run as ./exercise2
 */

#include <stdio.h>

int main(int argc, char **argv)
{
    int count = 10;
    int *temp = 0;
    int sum = 0;

    temp = &count;
    *temp = 20;

    temp = &sum;
    *temp = count;

    printf("count = %d, *temp = %d, sum = %d\n", count, *temp, sum);

    return 0;
}
