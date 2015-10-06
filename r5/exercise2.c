//
// Some pointer exercises
//

#include <stdio.h>

int   f1(int  x);
void  f2(int *x);
int   f3(int *x);
int  *f4(int  x);


int main () {

  int a,b;

  a = 42;
  printf("%d ", f1(a));

  a = 42;
  f2(&a);
  printf("%d ", a);

  a = 42;
  b = f3(&a);
  printf("%d %d ", a, b);

  a = 42;
  printf("%d ...\n", *f4(a));

  return 0;
}

// Returns  x - 40
int f1 (int x) {

  // Your code here

  return x;
}

// Divides the value stored at the address
// given by x by 14.
void f2 (int *x) {

  // Your code here

}

// Modifes the value at x by dividing it 
// (without remainder) by 8. Returns the
// number of times [ floor(x/8)+1 ] goes
// into (the original) x.
int f3 (int *x) {


  return 0;
}

// Returns a pointer to  gcf(a,b) where 
// a = x + [base computers work in] and 
// b = x + [x written backwards] (for x
// written in base 10).
int *f4 (int x) {

  return NULL;
}


