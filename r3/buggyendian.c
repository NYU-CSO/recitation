/* this program is supposed to 
 * convert of an array of ints (in naive little endian format)
 * to an array of ints (in big endian format)
 */
#include <stdio.h>

void
EndianFlip(int number) {
	char *p = (char *)&number;
	char tmp[4]; 
	//fill the tmp array byte by byte, in the reverse order of the p array
	for (int j = 0; j < 4; j++) {
		tmp[j] = p[4-j];
	}
	number = *(int *)tmp;
}

int main(int argc, char **argv)
{
	int array[5] = {1,2,3,4,5};

	for (int i = 0; i < 5; i++) {
		EndianFlip(array[i]); //turn little endian or big endian or vice versa
	}
	
	printf("The first element of the flipped arrays is %08x\n", array[0]);
    return 0;
}
