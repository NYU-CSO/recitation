//
// Some other pointer exercises.
//
// Please ONLY USE pointer; for
// example, you should never use
// array[i]!
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_array(int *array, int length);
char *print_array(int *array, int length);
char *join_strings(char *a, char *b);

int main()
{
    int f[8] = {11, 8, 5, 3, 2, 1, 1, 0};

    char *s1 = print_array(f, 8);
    printf("%s\n", s1);

    reverse_array(f, 8);
    char *s2 = print_array(f, 8);
    printf("%s\n", s2);

    free(s1);
    free(s2);

    return 0;
}

// Reverses the array *in place*
void reverse_array(int *array, int length)
{
    int i = 0;
    for (i = 0; i < (length / 2); i++)
    {
        int temp = *(array + i);
        *(array + i) = *(array + length - i - 1);
        *(array + length - i - 1) = temp; 
    }
}

// Returns a pointer to a null-terminated char
// array which contains the given array in the
// form: "array = [a0, a1, a2, ... , an]"
char *print_array (int *array, int length)
{
    // note: all calls to join_strings must be pointers
    // to values stored on the heap (via malloc)
    
    // initially holds a blank string
    char *str = (char *)malloc(sizeof(char) * 11);
    memset(str, 0, sizeof(char) * 11);
    strncpy(str, "array = [ ", 10);

    int i = 0;
    for (i = 0; i < length - 1; i++)
    {
        int elem = *(array + i);
        // the max value of a signed int is ~2.1 billion, or 10 digits
        // 11 with negative sign, 12 with space, 13 with comma,
        // 14 with null terminator
        char *int_str = (char *)malloc(sizeof(char) * 14);
        memset(int_str, 0, sizeof(char) * 14);
       
        // see man snprintf if you're unsure on what it does 
        snprintf(int_str, 13, "%d, ", elem);
        str = join_strings(str, int_str);
    }
    // last elem of array should not have trailing comma
    int elem = *(array + length);
    char *int_str = (char *)malloc(sizeof(char) * 13);
    memset(int_str, 0, sizeof(char) * 13);
    snprintf(int_str, 12, "%d ", elem);
    str = join_strings(str, int_str);

    // in order to use join_strings, our end bracket string must be on the heap
    char *end_bracket = (char *)malloc(sizeof(char) * 2);
    memset(end_bracket, 0, sizeof(char) * 2);
    strncpy(end_bracket, "]", 1);

    char *final_str = join_strings(str, end_bracket);
        
    return final_str;
}

// joins the two strings together
// assumes both are null terminated
// assumes both are on the heap
char *join_strings(char *a, char *b)
{
    int a_len = strlen(a);
    int b_len = strlen(b);
    // includes a spot for the null terminator
    int len = a_len + b_len + 1;

    char *newstr = (char *)malloc(sizeof(char) * len);
    memset(newstr, 0, sizeof(char) * len);
 
    strncpy(newstr, a, a_len);
    strncpy(newstr + a_len, b, b_len);
 
    free(a);
    free(b);

    return newstr;
}
