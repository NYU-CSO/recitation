//
// Some other pointer exercises.
//
// Please ONLY USE pointer; for
// example, you should never use
// array[i]!
// 

#include <stdio.h>
#include <stdlib.h>


void reverse_array(int * array, int length);
char *print_array(int * array, int length);

int main () {

  int f[8] = {11, 8, 5, 3, 2, 1, 1, 0};

  char *s1 = print_array(f, 8);

  reverse_array(f, 8);
  char *s2 = print_array(f, 8);

  free(s1);
  free(s2);

  return 0;
}


// Reverses the array *in place*
void reverse_array (int * array, int length) {

  // Your code here

}

// Returns a pointer to a null-terminated char 
// array which contains the given array in the
// form: "array = [a0, a1, a2, ... , an]"
char * print_array (int * array, int length) {

  // Your code here

  return NULL;
}
