Tutorial 8 Solutions
=========

Git
-----
These exercises are meant for you to do and see how Git works.

Compiling
-----
These exercises are meant for you to do and see how to compile code. There is one compiler warning present in this exercise, and the walkthrough is provided in the exercise itself.

Debugging memory-related errors
-----
In `library.c` on line 8, we malloc `len` bytes for a string, copy our parameter string into it, print it, and return. It is never freed. So after the `printf` call, we need to add
````c
free(str);
````
to prevent the memory leak. Don't forget to recompile both the object file and the binary.

If we run Memcheck (the default tool when using Valgrind) on the binary (we will call it `bug`) produced from compiling `buggy-code.c`, there are two errors. One is an invalid write on line 14 that says an address is 0 bytes after a size of 20 alloc'd. The other is that there was 1 alloc on the heap and 0 frees. The first error implies that we went out of bounds while writing in an array that is 20 bytes big. On line 12, we see that the loop condition is incorrect and causes the out of bounds, and instead the loop should read
````c
for (i = 0; i < numints; i++)
````
We also never free our alloc'd array `arr`. Let's free it right before the `return 0;` statement at the end of the file.
````c
free(arr);
````

In the executable `buggy-executable`, it seems that we are writing to an address that is read-only. We have seen this before, and it's because the string is allocated in the read-only data segment. The source code, `buggy-executable.c` is provided here:
````c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *str = "Joay Billy Bob";

    printf("String: %s\n", str);
    printf("Oops, seems that we misspelled Joey\n");

    str[2] = 'e';
    printf("Fixed string: %s\n", str);

    return 0;
}
````
The segmentation fault happens because of the line `str[2] = 'e';`. One fix is to instead allocate the string onto the (read-write) data segment by changing the declaration from `char *str` to `char str[15]` where 15 is the length of the string "Joay Billy Bob" and an extra byte for the null terminator.

Types and Typedef
-----
Here is some code that will determine the sizes of the various types and its output
````c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    printf("Printing out sizes of various types\n");

    // sizeof returns a long unsigned int, so we use %lu while printing
    printf("sizeof(int) = %lu\n", sizeof(int));
    printf("sizeof(char) = %lu\n", sizeof(char));
    printf("sizeof(float) = %lu\n", sizeof(float));
    printf("sizeof(long long) = %lu, sizeof(long) = %lu\n", sizeof(long long), sizeof(long));
    printf("sizeof(double) = %lu\n", sizeof(double));
    printf("sizeof(size_t) = %lu\n", sizeof(size_t));
    printf("sizeof(unsigned int) = %lu\n", sizeof(unsigned int));
    printf("sizeof(time_t) = %lu\n", sizeof(time_t));

    int a = 7;
    printf("Printing out sizes of various variables of various types\n");
    printf("sizeof(a) = %lu where a is declared as int a\n", sizeof(a));

    double b = 4.2;
    printf("sizeof(b) = %lu where b is declared as double b\n", sizeof(b));

    char c[10] = { 0 };
    printf("sizeof(c) = %lu where c is declared as char c[10]\n", sizeof(c));

    char *d = (char *)malloc(sizeof(char) * 10);
    memset(d, 0, sizeof(char) * 10);
    printf("sizeof(d) = %lu where d is declared as char *d and points to 10 characters on the heap\n", sizeof(d));
    free(d);

    int e[20] = { 0 };
    printf("sizeof(e) = %lu where e is declared as int e[20]\n", sizeof(e));

    return 0;
}
````
````
Printing out sizes of various types
sizeof(int) = 4
sizeof(char) = 1
sizeof(float) = 4
sizeof(long long) = 8, sizeof(long) = 8
sizeof(double) = 8
sizeof(size_t) = 8
sizeof(unsigned int) = 4
sizeof(time_t) = 8
Printing out sizes of various variables of various types
sizeof(a) = 4 where a is declared as int a
sizeof(b) = 8 where b is declared as double b
sizeof(c) = 10 where c is declared as char c[10]
sizeof(d) = 8 where d is declared as char *d and points to 10 characters on the heap
sizeof(e) = 80 where e is declared as int e[20]
````

Note that the compiler knows as compile-time how big the arrays `c` and `e` are. `c` holds 10 characters, each is 1 byte big, so `c` holds 10 bytes. `e` holds 20 integers, each integer is 4 bytes big, so `e` holds 80 bytes.

So the output of the block of code declaring two character arrays should give us
````
10 8
````

C Preprocessor Macros
-----
Note: if you compile with the flag `-g3`, you can use macros while debugging.

The solutions for the various bit extraction macros are:
````c
#include <stdio.h>

#define ENABLEBIT(bitstring, index) (bitstring = bitstring | (1 << index))
#define DISABLEBIT(bitstring, index) (bitstring = bitstring & ~(1 << index))
#define EXTRACTBIT(bitstring, index) ((bitstring & (1 << index)) >> index)

int main()
{
    int a = 0;
    ENABLEBIT(a, 5);
    printf("This value should be 32: %d\n", a);

    a = 15;
    DISABLEBIT(a, 2);
    printf("This value should be 11: %d\n", a);

    a = 17;
    printf("This value should be 1: %d\n", EXTRACTBIT(a, 4));
    printf("This value should be 0: %d\n", EXTRACTBIT(a, 3));

    return 0;
}
````
