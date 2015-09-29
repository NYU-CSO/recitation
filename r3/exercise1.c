/*
 * Compile as gcc -g exercise1.c -o exercise1
 * Run as ./exercise1
 */

#include <stdio.h>

// iterative method to calculate length
int stringlen(char *str)
{
    int len = 0;
    // '\0' means null character, or end of string
    while (*str != '\0')
    {
        str++;
        len++;
    }
    return len;
}

// alternative to iterative method; differs in how the value at the pointer is accessed
int stringlen2(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

// recursive method to calculate length
int stringlen3(char *str)
{
    if (*str == '\0')
        return 0;
    return 1 + stringlen3(str + 1);
}

void RSCase(char *str)
{
    int i = 0;
    while (str[i] != 0) // equivalent to != '\0'
    {
        // see if our current character is a lowercase letter
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            // what cases must we capitalize the letter?
            // first character of string
            if (i == 0)
            {
                str[i] = str[i] - 'a' + 'A';
            }
            // previous character is a space (and we aren't at the first character of the string)
            if (i > 0 && str[i - 1] == ' ')
            {
                str[i] = str[i] - 'a' + 'A';
            }
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    char string[18] = "lenny writes code";
    printf("%d %d %d\n", stringlen(string), stringlen2(string), stringlen3(string));
    RSCase(string);
    printf("%s\n", string);
    return 0;
}
