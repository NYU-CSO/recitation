

#include <stdio.h>
#include <stdlib.h>


void increment(int *x);


int main () {
  int a = 5;

  int *b = (int *)malloc(sizeof(int)); 
  *b = 27;

  unsigned int *c = (unsigned int *)malloc(sizeof(unsigned int) * 5);
  c[0] = 495;
  c[1] = 8127;
  c[2] = 3355033609;
  c[3] = (unsigned int)a;
  c[3] = (unsigned int)b;


  // TODO QUESTIONS:
  // What types are a, b, & c?
  // What is the value of a, b, c?

  // TODO EXERCISE:
  // Use the function "increment" to 
  // add one to each of a, b, c[...]

  // TODO QUESTIONS:
  // Which of the following calls are 
  // ALWAYS valid?
  // (i)    *a      = 1;
  // (ii)   *b      = 2;
  // (iii)  *(c+x)  = 3;  // (for which x?)
  // (iv)   **a     = 4;
  // (v)    **b     = 5;
  // (vi)   **(c+x) = 6;  // (for which x?)
  
  
  free(b);
  free(c);
}


// Increments the value stored in x by
// one.
void increment (int *x) {

  // Your code here

}




