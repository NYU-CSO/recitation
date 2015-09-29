#include <stdio.h>
#include <stdlib.h>

int checkEquality(int x, int y)
{
    if (x=y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// the character at the index "n" should be changed to newchar
// "n" is zero-indexed
void editCharAt(char **str, int n, char newchar)
{
    // your code here
}

int main(int argc, char **argv)
{
    char *string = "How can Mirrors Be Real If Our Eyes Aren't Real?";
    // now call editCharAt
    printf("%s\n", string);
    printf("Equality of 4 and 5: %d\n", checkEquality(4, 5));
    return 0;
}
