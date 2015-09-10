/**
 * This is the most basic form of hello world you can write
 * Some machines may complain that main has a non-integer return type
 * But our machine will not
 *
 * To compile, compile as gcc basic.c
 * To compile to a specific name, compile as gcc basic.c -o binary_name
 * To compile with debugging, compile as gcc -g basic.c -o debuggable_binary
 */


/**
 * in Java, to receieve input and output, we use System.in and System.out
 * in C, we also have standard input and standard output, but the libraries to use them
 * aren't included by default, so we must manually include the header files
 */
#include <stdio.h>

void main()
{
    // equivalent of System.out.printf
    printf("Hello world! (basic.c)\n");
}
