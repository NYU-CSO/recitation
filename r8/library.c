#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_string(char *string)
{
    int len = strlen(string) + 1;
    char *str = (char *)malloc(len);
    memset(str, 0, len);
    memcpy(str, string, len); 
    printf("%s", str);
}
