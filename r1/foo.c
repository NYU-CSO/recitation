#include <stdio.h>

void foo() {
	int sum = 0;
	int i = 1;
	while (i <= 10) {
		sum += i;
	}
	printf("foo: sum of 1...10 is %d\n", sum);
}
