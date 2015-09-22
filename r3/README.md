Tutorial 3
==========

Exercise 1 -- String Length / RuneScape Case
-----
```c
#include <stdio.h>

int strlen(char *str)
{
	// your code here
}

void RSCase(char *str)
{
	// your code here (modify char *str in place)
}

int main(int argc, char **argv)
{
	char *string = "lenny writes code";
	printf("%d\n", strlen(string));
	RSCase(string);
	printf("%s\n", string);
	return 0;
}
```
Write the function strlen that calculates the length of the input string (length of `"bob"` is 3), and the function RSCase that capitalizes the first character of each word (turns `"hello Bob my name is Joe"` to `"Hello Bob My Name Is Joe"`).

Exercise 2 -- Pointer Programming
-----
```c
int  count = 10, *temp, sum = 0;
temp = &count;
*temp = 20;
temp = &sum;
*temp = count;
printf("count = %d, *temp = %d ,sum = %d\n", count, *temp, sum);
```
What is the output of this code (without running it explicitly)?

Exercise 3 -- Strstr
-----
```c
#include <stdio.h>

char *strstr(char *haystack, char *needle, int *index)
{
	// your code here
}

int main(int argc, char **argv)
{
	char *bigstring = "look at our code, our code is amazing";
	char *smallstring = "our code";
	int index;
	char *substring = strstr(bigstring, smallstring, &index);
	printf("substring: %s\nindex: &d\n", substring, index);
	return 0;
}
```

Exercise 4 -- The Seg Fault In Our Char Stars
-----
Lenny wanted to check his understanding of strings in C and pointers, and he wrote the following code

```c
#include <stdio.h>

int main(int argc, char **argv)
{
	char **s;
	char foo[] = "Hello World";

	*s = foo;
	printf("s is %s\n", s);

	s[0] = foo;
	printf("s[0] is %s\n", s[0]);
	return 0;
}
```
What happens with this program is run? Can you figure out on what line the error(s) occurs, and why?

Exercise 5 -- Debug a C program
-----

Lenny is asked to write a program that turn an array of integers in little
endian representation into an array of integers in big endian format.  His
C code is the file `buggyendian.c`.   What should the program print out
if Lenny's code were correct? Compile `buggyendian.c` (do `gcc -std=c99 buggyendian.c`)
and run it (`./a.out`).  Does Lenny's program print out the correct value?

Please debug Lenny's program.  Unlike solving a math problem, we don't debug
by just staring at the program for extended periods of time, however tempting
that might be.  This is because we usually make errors by having a wrong
understanding/assumption on how something works, thus, staring at the code
while still holding that wrong assumption won't move
us any further towards sniffing out the bugs.  We must do something to validate
our assumption/understanding. And this is why debugging is usually done by
adding lots of printf's and/or run the program in gdb to confirm what we think
the program is doing and should be doing.  In the process, we will discover
something unexpected (i.e. do i smell a bug?).

Below are some suggested steps (using printf or gdb to answer the question, and not just your brain):
* Find out what the array element i before and after the invocation of function EndianFlip?
* Find out the content of the array p?
* Find out the content of the tmp array before and after the loop in EndianFlip?

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
