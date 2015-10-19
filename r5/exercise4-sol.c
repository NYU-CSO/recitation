#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void increment(int *x);

int main()
{
    int a = 5;

    int *b = (int *)malloc(sizeof(int));
    *b = 27;

    unsigned int *c = (unsigned int *)malloc(sizeof(unsigned int) * 5);
    c[0] = 495;
    c[1] = 8127;
    c[2] = 3355033609;
    c[3] = (unsigned int)a;
    c[4] = (unsigned int)b;

    // TODO QUESTIONS:
    // What types are a, b, & c?
    // a: int
    // b: pointer to an int
    // c: pointer to an unsigned int (really a pointer to 5 unsigned ints that are contiguous in memory)
    // c[0] = *(c + 0): unsigned int
    // c[1] = *(c + 1): unsigned int
    // c[2] = *(c + 2): unsigned int
    // c[3] = *(c + 3): int casted to an unsigned int
    // c[4] = *(c + 4): pointer to an int casted to an unsigned int
    // What is the value of a, b, c?
    // a: 5
    // b: some address
    // c: some address
    // c[0] = *(c + 0): 495
    // c[1] = *(c + 1): 8127
    // c[2] = *(c + 2): 3355033609
    // c[3] = *(c + 3): 5
    // c[4] = *(c + 4): some address (that of b)

    // TODO EXERCISE:
    // Use the function "increment" to
    // add one to each of a, b, c[...]
    increment(&a);
    increment(b);
    increment(c + 0);
    increment(c + 1);
    increment(c + 2);
    increment(c + 3);
    // this increments the actual pointer, but has no effect on b itsel
    increment(c + 4);
    // this increments b, but do not call it if the above was called
    // as c + 4 will be an address, but we do not have explicit access to it
    // increment(*(c + 4));

    // TODO QUESTIONS:
    // Which of the following calls are
    // ALWAYS valid?
    // (i)    *a      = 1;
    // (ii)   *b      = 2;
    // (iii)  *(c+x)  = 3;  // (for which x?)
    // (iv)   **a     = 4;
    // (v)    **b     = 5;
    // (vi)   **(c+x) = 6;  // (for which x?)
    //
    // (i)    invalid, a is not a pointer
    // (ii)   valid, b is a pointer to an int, so *b is an int
    // (iii)  valid, c is a pointer to an unsigned int, so *(c + x) is an unsigned int
    //        (valid for x in [0, 4])
    // (iv)   invalid, a is an int, so *a is meaningless, then **b must be meaningless
    // (v)    invalid, b is a pointer to an int, so *b is an int, so **b is meaningless
    // (vi)   sometimes valid when *(c + x) is a pointer; this is only the case when
    //        x = 4 where *(c + x) is a pointer to an unsigned int, then **(c + x) is an
    //        unsigned int; another problem is that the sizeof(unsigned int) must be the
    //        same as sizeof(int *), which is not always the case; a third problem is that
    //        the value *(c + x) was incremented; so the validity of this line depends on
    //        if increment(c + 4) was called or (increment(*(c + 4));

    // if we run the following line, what happens is that *b goes from 28 (27 incremented)
    // to 1564, reason being that *(c + 4) is actually b + 1
    // 28 is 0x1c, 6 is 0x6, and 1564 is 0x61c, so you can see this in action
    // *(int *)*(c + 4) = 6;

    free(b);
    free(c);

    return 0;
}

// Increments the value stored in x by
// one.
void increment(int *x)
{
    (*x)++;
}
