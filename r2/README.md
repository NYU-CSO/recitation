Tutorial 2
==========


Exercise 1 -- "Signed Subtraction"
-----

Suppose we want to add two numbers on an x86 processor: 86 and -94. We know the answer is -8, but we want to see how these numbers are stored in memory, added, then stored again.

Let the number 86 be stored at address `0x00` and let the number -94 be stored at the address `0x04`. (What decimal numbers do `0x00` and `0x04` represent? Why are they not consecutive?) Further, let the result, -8, be stored at address `0x08`.

Draw the memory before the addition operation and after the addition operation in hexadecimal.

Rather than convert -8 into 32-bit signed integer directly, calculate -8 via the addition of 86 and -94 as 32-bit signed integers.



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


Exercise 5 -- "Macro Management"

Consider the following code:

```c
#include <stdio.h>
#include <math.h> // to get the value of pi

#define MAX_STR_LEN 100
#define PI 3.14159265
#define E 2.71828
#define EPSILON 0.00001

// fabs gets the absolute value for float/double
#define CLOSE(x, y) (fabs(x - y) < EPSILON)

int main() {
   double value = M_PI; // the real value of pi given to us from math.h
   printf("%d\n", CLOSE(value, PI));
   value = 2.7;
   printf("%d\n", CLOSE(value, E));
   return 0;
}

```

What is the output of the program?
