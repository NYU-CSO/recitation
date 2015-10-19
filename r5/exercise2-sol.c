//
// Some pointer exercises
//

#include <stdio.h>
#include <stdlib.h> // required for malloc/free
#include <string.h> // required for memset

int f1(int x);
void f2(int *x);
int f3(int *x);
int *f4(int x);
int gcd(int a, int b);
int backwards(int n);

int main()
{
    int a, b;

    a = 42;
    printf("%d ", f1(a));

    a = 42;
    f2(&a);
    printf("%d ", a);

    a = 42;
    b = f3(&a);
    printf("%d %d ", a, b);

    a = 42;
    int *result = f4(a);
    printf("%d ...\n", *result);
    free(result); 

    return 0;
}

// Returns x - 40
int f1(int x)
{
    return x - 40;
}

// Divides the value stored at the address
// given by x by 14.
void f2(int *x)
{
    *x = (*x) / 14;
}

// Modifes the value at x by dividing it
// (without remainder) by 8. Returns the
// number of times [ floor(x/8)+1 ] goes
// into (the original) x.
int f3(int *x)
{
    int oldx = *x;

    // holds floor(x/8)+1
    int expr = 0;
    if (oldx < 0)
    {
        expr = oldx / 8;
    }
    else
    {
        expr = oldx / 8 + 1;
    }
    
    *x = (*x) / 8;

    return oldx / expr;
}

// Returns a pointer to gcf(a,b) where
// a = x + [base computers work in] and
// b = x + [x written backwards] (for x
// written in base 10).
//
// where will the actual integer gcf(a,b) be stored?
// we can't have a pointer to a value on the stack, so
// it must be on the heap (via malloc)
int *f4(int x)
{
    int a = x + 2;
    int b = x + backwards(x);
    
    int *gcf = (int *)malloc(sizeof(int));
    memset(gcf, 0, sizeof(int));

    // we can calculate gcf(a,b) using the Euclidian algorithm
    *gcf = gcd(a, b);

    return gcf;
}

// assume a,b are non-negative
int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }

    return gcd(b, a % b);
}

// returns n backwards in base 10
int backwards(int n)
{
    int result = 0;
    int neg = 0;
    if (n < 0)
    {
        n = -n;
        neg = 1;
    }
    while (n > 0)
    {
        int digit = n % 10;
        result = result * 10 + digit;
        n = n / 10;
    }
    if (neg)
    {
        return -1 * result;
    }
    return result;
}
