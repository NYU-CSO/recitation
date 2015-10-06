#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// the character at the index "n" should be changed to newchar
// "n" is zero-indexed
void editCharAt(char **str, int n, char newchar)
{
    // first check pointer validity for str, then pointer validity for *str
    // we use short circuiting as to not check *str == NULL (which would lead to a segmentation fault) if str == NULL
    if (str == NULL || *str == NULL)
        return;

    // str is a pointer to a pointer to a character
    // simplified, str is a pointer to a string
    // then *str is the actual string
    int len = strlen(*str);

    // check out of bounds
    if (n >= len || n < 0)
        return;

    // *str is a pointer to the first (0th) character in the string
    // then *str + n is a pointer to the nth character in the string
    // this is the line that causes the segmentation fault if we tried working with the variable 'string'
    *(*str + n) = newchar;
}

int main(int argc, char **argv)
{
    char *string = "How can Mirrors Be Real If Our Eyes Aren't Real?";

    // the string pointed to by the variable string lives in the data segment
    // this area is read-only, so we need to use a different area in memory
    // to fix, we will instead allocate explicitly an array of enough size on the heap, and copy our string there
    char *editableString = (char *)malloc(sizeof(char) * (strlen(string) + 1));

    // now that we have allocated memory, set it to an initialized state of all 0s as to not work with garbage data
    memset(editableString, 0, sizeof(char) * strlen(string) + 1);

    // copy over the string, see "man 3 strcpy" for details
    // strncpy is used to explicitly show how many bytes will be copied
    strncpy(editableString, string, strlen(string) + 1);

    // now call editCharAt with the right parameters (make sure types match)
    editCharAt(&editableString, 4, 'C');

    // now that our string has been edited, let's point the variable "string" to the string held at variable "editedString"
    string = editableString;

    printf("%s\n", string);

    // don't forget to cleanup any allocated memory when finished with it
    // we are done when our program ends
    free(editableString);

    return 0;
}
