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
	//to make sure i have not copies more than allocated number of bytes
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
such string functions. Say, you want to use `strlen`, include the `string.h` header file and 
type `man strlen` to see its documentation.

C's string library is quite spartan, compared with the string libraries
available in other modern languages, such as Python or Go.  For example, there
is no ``join`` facility whereby programmers can combine many strings together
into a single one.  Your professor implemented join function, shown above, but 
it does not seem to work right. For example, when she types `./a.out hello world` 
The program prints out `Joined arguments are: ./a.outhelloworld*` whereas the 
correct one should be `Joined arguments are: ./a.out*hello*world*`. Rumor also
has it that she's not doing malloc right. Please help her debug `join.c`. Tell us 
what steps you took to pinpoint the bug. We are interested.




