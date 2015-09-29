/* this program is supposed to
 * convert of an array of ints (in naive little endian format)
 * to an array of ints (in big endian format)
 */
#include <stdio.h>

// the parameter needs to be a pointer to an int rather than a raw int
// the reason for this is if the parameter was a raw int, a copy of
// the parameter would be made, and any local changes would be lost
// when the function returns
void EndianFlip(int *number)
{
    char *p = (char *)number;
    char tmp[4];
    //fill the tmp array byte by byte, in the reverse order of the p array
    for (int j = 0; j < 4; j++)
    {
        tmp[j] = p[3-j];
        // our p array is defined from p[0] to [3], and j is defined from 0 to 3
        // so p[4-j] is defined from p[1] to p[4], where p[4] is out of bounds
        // fix by changing to p[3-j] to fix the off-by-one error
    }
    *number = *(int *)tmp;
}

int main(int argc, char **argv)
{
    int array[5] = {1,2,3,4,5};

    for (int i = 0; i < 5; i++)
    {
        // don't forget to check the parameter types
        EndianFlip(&array[i]); //turn little endian or big endian or vice versa
    }

    printf("The first element of the flipped arrays is %08x\n", array[0]);
    return 0;
}

