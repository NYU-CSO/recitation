/*
 * Compile as gcc -g exercise2.c -o exercise2
 * Run as ./exercise2
 */

#include <stdio.h>

void f(int p, int q)
{
    p = q;
}

void g(int *p, int q)
{
    p = &q;
}

void h(int *p, int q)
{
    *p = q;
}

int main(int argc, char **argv)
{
    int a, b;
    a = 9; b = 2;

    f(a, b); 
    printf("%d %d\n", a, b); 

    a = 9; b = 2;
    g(&a, b); 
    printf("%d %d\n", a, b); 

    a = 9; b = 2;
    h(&a, b); 
    printf("%d %d\n", a, b); 

    return 0;
}

