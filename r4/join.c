#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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



