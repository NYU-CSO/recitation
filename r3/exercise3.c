#include <stdio.h>

int strlen(char *s)
{
    int i=0;
    while (s[i++] != 0) ;
    return i;
}

char *strstr(char *haystack, char *needle)
{
    int i,j;
    
    for (i=0; i<=strlen(haystack)-strlen(needle); ++i) 
    {
        for (j=0; j<=strlen(haystack); ++j)
        {
            if (j == strlen(needle)) return haystack + i;
            if (haystack[i+j] != needle[j]) break;
        }
    }

    return NULL;
}

int main(int argc, char **argv)
{
    char *bigstring = "look at our code, our code is amazing";
    char *smallstring = "our code";
    char *substring = strstr(bigstring, smallstring);
    printf("substring: %s\n", substring);
    return 0;
}