Tutorial 3
==========

Exercise 1 -- Debug a C program
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
