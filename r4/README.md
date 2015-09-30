Tutorial 4
==========
Exercise 1 -- The Buggy String Join
-----
```c
//combine an array of strings (of length num_strings)
//into one string in which the constituent strings are separated by
//the separator string
char *
join(int num_strings, char *strings[], char *separator)
{
	int total_len = 0;
	for (int i = 0; i < num_strings; i++) {
		total_len += strlen(strings[i]); //see "man strlen"
	}

	//allocate a new array whose length is the sum of the length of each individual string
	char *result = (char *)malloc(total_len);

	char *start = result;
	for (int i = 0; i < num_strings; i++) {
		strcpy(start, strings[i]); //see "man strcpy"
		start += strlen(strings[i]);
		strcpy(start, separator);
	}
	//to make sure i have not copied more than the allocated number of bytes
	assert((start - result) <= total_len);
	return result;
}

int
main(int argc, char *argv[])
{
	printf("Joined arguments are: %s\n", join(argc, argv, "*"));

}
```
In the last tutorial, we have asked you to implement various common functions to manipulate string,
such as computing the length of a string, etc.  The C's standard library already includes many
useful string functions that one can readily use. Just type `man string` to see a list of
such string functions. Say, you want to use `strlen`, add the line `#include <string.h>` and
type `man strlen` to see its documentation.

C's string library is quite spartan, compared with the string libraries
available in other modern languages, such as Python or Go.  For example, there
is no ``join`` facility whereby programmers can combine many strings together
into a single one.  Your professor implemented join function, shown above, but
it does not seem to work right. For example, when she types `./a.out hello world`
The program prints out `Joined arguments are: ./a.outhelloworld*` whereas the
correct output should be `Joined arguments are: ./a.out*hello*world*`. Rumor also
has it that she's not doing malloc right. Please help her debug `join.c`. Tell us
what steps you took to pinpoint the bug. We are interested.


Exercise 2 -- Binary Tree Mon Amour
-----

You are starting at your first internship job at company C-Lover.  Someone else
has written a set of C functions that implements a binary tree.  The function
`insert` inserts a value into the binary tree.  The function `exists` searches
the tree for the specified value. If the value is found in the tree, it returns
1, otherwise it returns zero.  These functions are available in `tree.c`

Please design and write some code to test the correctness of the binary tree
operations.  For simplicity, you can write these tests in the `main` function.
Show us your test code.  If our `tree.c` does not pass your test, debug it
and tell us the steps you took to eventually emerge victorious


Exercise 3 -- The Incorrect If
-----

In the file `exercise3.c`, we have written a function `checkEquality` thats checks the equality of two variables, and is broken. By using GDB, figure out the broken line of code, and the fix for it. Once you've figured out the broken line of code, can you think of why the code behaves that way?

Exercise 4 -- Modifying Strings in Place
-----

Lenny found a celebrity he wishes to emulate on a social media platform, and wrote a string to send out. Unfortunately, he made a mistake while writing the string. In the file `exercise4.c`, Lenny has written code to fix his mistake. He wants to edit the nth character of a string (n is 0-based) to a certain character. Boilerplate code has been provided. Write the code for `editCharAt`. Don't forget to use GDB as a debugging tool if needed. The use of the following libraries is recommended: `string.h`, `stdlib.h`.
