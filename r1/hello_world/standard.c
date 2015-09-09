/**
 * This version of hello world uses the standard conventions for declaring main and its inputs
 * In Java, the main method returns void, but the process has a return value. 0 means the program
 * completed successfully, and non-zero represents an error.
 * In C, we can explicitly set a return value (in Java, we do so using System.exit), and the main
 * function returns said value.
 *
 * In Java, the input to our main function is a String array (generally called args). These are
 * the command line arguments.
 * In C, we also have the command line arguments. The first one is always
 * the name of the executable instead. As you will learn, we cannot tell array lengths in C like we can
 * in Java where we could do args.length.
 * Therefore in C, we must give the array length as another parameter.
 */

#include <stdio.h>

int main(int argc, char **argv)
{
    printf("Hello world! (standard.c)\n");
    return 0;
}
