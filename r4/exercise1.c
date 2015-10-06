/*
 * Compile as gcc -g -std=c99 exercise1.c
 *
 * the C99 flag is for the ability to declare variables inside of a for loop
 * example:
 *
 * int n = 10;
 * int i = 0;
 * for (i = 0; i < n; i++)
 * {
 *     printf("%d\n", i);
 * }
 *
 * versus
 *
 * int n = 10;
 * for (int i = 0; i < n; i++)
 * {
 *     printf("%d\n", i);
 * }
 *
 * in order for the second snippet to work, we must use the C99 flag
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * combine an array of strings (of length num_strings)
 * into one string in which the constituent strings are separated by
 * the separator string
 */
char *join(int num_strings, char *strings[], char *separator)
{
    int total_len = 0;
    for (int i = 0; i < num_strings; i++)
    {
        total_len += strlen(strings[i]); // see "man strlen"
    }
    
    // allocate space for all the separators (which is also present at the end of the string)
    total_len += strlen(separator) * num_strings;

    // allocate space for the null terminator
    total_len++;

    // allocate a new array whose length is the sum of the length of each individual string
    // characters are one byte, however if we were working with other data type
    // we'd need to account for their size when calling malloc
    char *result = (char *)malloc(total_len * sizeof(char));

    // good idea to memset after malloc to prevent working with garbage data
    memset(result, 0, total_len * sizeof(char));

    char *start = result;
    for (int i = 0; i < num_strings; i++)
    {
        strcpy(start, strings[i]); // see "man strcpy"
        start += strlen(strings[i]);
        strcpy(start, separator);
        start += strlen(separator); // shift over the pointer to after the separator
    }

    // to make sure we have not copied more than the allocated number of bytes
    // don't forget to account for the null terminator
    assert((start + 1 - result) <= total_len);
    return result;
}

// argv are the command line parameters (including the executable name)
// argc is the number of command line parameters
int main(int argc, char *argv[])
{
    char *joined = join(argc, argv, "*");
    printf("Joined arguments are: %s\n", joined);
    
    // malloc was called inside the join function
    free(joined);

    return 0;
}
