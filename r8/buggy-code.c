#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int numints = 5;
    int *arr = (int *)malloc(sizeof(int) * numints);
    memset(arr, 0, sizeof(int) * numints);
    
    int i = 0;
    for (i = 0; i <= numints; i++)
    {
        arr[i] = i;
        printf("Successfully set array at index %d to %d\n", i, i);
    }

    return 0;
}
