#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEquality(int x, int y)
{
    // if (x=y)
    // the problem is that the assignment happens, and assignments are always true
    if (x == y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char **argv)
{
    printf("Equality of 4 and 5: %d\n", checkEquality(4, 5));

    return 0;
}
