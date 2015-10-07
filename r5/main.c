#include <stdio.h>
long
addone2(long x)
{
	x++;
	return x;
}

long
addone(long *x) 
{
	(*x)++;
	return *x; 
}

int main()
{
	long x = 1;
	long rx;

	rx = addone2(x);
	printf("x=%ld rx=%ld\n", x, rx);

	rx = addone(&x);
	printf("x=%ld rx=%ld\n", x, rx); 

	rx = addone((long *)x);
	printf("x=%ld rx=%ld\n", x, rx); 
}

