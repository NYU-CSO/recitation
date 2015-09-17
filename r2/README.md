Tutorial 2
==========


Exercise 1 -- "Signed Subtraction"
-----

Suppose we want to add two numbers on an x86 processor: 86 and -94. We know the answer is -8, but we want to see how these numbers are stored in memory, added, then stored again.

Let the number 86 be stored at address `0x00` and let the number -94 be stored at the address `0x04`. (What decimal numbers do `0x00` and `0x04` represent? Why are they not consecutive?) Further, let the result, -8, be stored at address `0x08`.

Draw the memory before the addition operation and after the addition operation in hexadecimal.

Rather than convert -8 into 32-bit signed integer directly, calculate -8 via the addition of 86 and -94 as 32-bit signed integers.

Once you've gotten the answer down, can you think of a way to check its correctness?
Hint: you can write a C program and use `gdb` to examine the memory.  Consider using the gdb command `x` (short for examine).

Exercise 2 -- "Fun with C & Pointers"
-----

Consider the following code:

```c
#include <stdio.h>

void f(int p, int q) { p = q; }
void g(int* p, int q) { p = &q; }
void h(int* p, int q) { *p = q; }

int main() {
  int a, b;
  a = 9; b = 2;

  f(a, b);
  printf("%d %d\n", a, b);

  a = 9; b = 2;
  g(&a, b);
  printf("%d %d\n", a, b);

  a = 9; b = 2;
  h(&a, b);
  printf("%d %d\n", a, b);

  return 0;
}
```

What is the output of the program?



Exercise 3 -- "The Confused Compiler"
-----


Lenny writes the following code:

```c
01  float a = 64.0;
02  int b = 1073741825; // = 2^30 + 1
03  a *= -1.0;
04  
05  a += b;
06  
07  printf("-a + b = %f \n", a);
```

... but the compiler gets confused at line 5 and misinterprets the value stored in `a` to be an integer and performs standard signed arithmetic on it and `b`. Then, on line 7, it remembers the value stored in `a` is a float and prints out its float representation.

Write (in hex) the values that live at both `&a` and `&b` at lines 4 and 6, then write what ends up being printed to the screen.

Again, check the correctness of your answer using gdb.

Exercise 4 -- "Binary Bonanza"
-----

Write the function printb() (in C!) that takes a pointer to a 4 byte value and prints its binary representation (preceded by `0b`).

```c
int main (int argc, char **argv) {

  int    a = 42;
  float  b = 13.37;

  printb(&a);
  printb(&b);

  return 0;
}

void printb (void *p) {
  // ... your code here ...
}
```

Brownie-points: Don't print out any of the leading zeros!


Exercise 5 -- Debug a C program
-----

Lenny is asked to write a program that turn an array of integers in little
endian representation into an array of integers in big endian format.  His
C code is the file `buggyendian.c`.   What should the program print out 
if Lenny's code were correct? Compile `buggyendian.c` (do `gcc -std=c99 buggyendian.c`)
and run it (`./a.out`).  Does Lenny's program print out the correct value?

Please debug Lenny's program.  Unlike solving a math problem, we don't debug 
by just staring at the program, however tempting that might be.  We add
printf's and run the program in gdb to validate what we think the program is
doing and should be doing.

Below are some suggested steps (using printf or gdb to answer the question, and not just your brain):
* What is the array element i before and after the invocation of function EndianFlip?
* What is the content of the array p?
* What is the content of the tmp array before and after the loop in EndianFlip?

```c
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

void main()
{
	int array[5] = {1,2,3,4,5};

	for (int i = 0; i < 5; i++) {
		EndianFlip(array[i]); //turn little endian or big endian or vice versa
	}
	
	printf("The first element of the flipped arrays is %08x\n", array[0]);
}
```
