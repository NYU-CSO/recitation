Practice Midterm Solutions
-----

Problem 1:
---
Binary representation of 0 is just `0`, or in six bits, `00 0000`.

For -6, let's first see what +6 is in twos complement form. 6 = 4 + 2 so the binary form is `00 0110`. Therefore -6 must be `111010`.

If we have the binary number `01 0010`, this must be a positive value. Therefore the value is simply 2 + 16, or 18.

`ux` is an unsigned int derived from the value of the signed int `x`. `x` is -17. +17 = 16 + 1, or `01 0001` in binary. Therefore -17 in binary is `101111`. Now we simply take this binary number and interpret it as an unsigned int to get 1 + 2 + 4 + 8 + 32, or 47.

`y` is a 3 bit short representing -3. +3 = 2 + 1, or `011`. Then -3 = `101`. As an aside, if we wanted to store `y` using 6 bits, and we knew `y` in 3 bits was `101`, we would perform sign extension (as in pad the binary using the sign bit of the original value) to get `11 1101`

`TMax` is the maximum value of a signed integer. This is `01 1111`, or 31.

`TMin` is the minimum value of a signed integer. This is `10 0000`, or -32 (the expression should read `TMin` not `-TMin`).

Problem 2:
---
````c
int mat1[M][N];
int mat2[N][M];

int sum_element(int i, int j)
{
  return mat1[i][j] +  mat2[i][j];
}
````
````
movslq %esi, %rsi
# holds the second parameter j

movslq %edi, %rdi
# holds the first parameter i

leaq (%rsi,%rdi,8), %rdx
# rdx = rsi + 8*rdi = j + 8i

leaq (%rdi,%rdi,4), %rax
# rax = rdi + 4*rdi = 5*rdi = 5i

leaq (%rdi,%rax,2), %rax
# rax = rdi + 2*rax = i + 2*5i = 11i

addq %rax, %rsi
# rsi = rsi + rax = j + 11i

movl mat2(,%rsi,4), %eax
# eax = *(mat2 + 4*rsi), or equivalent mat2[rsi] if we know mat2 is an array holding 4 byte values (which it is, ints)

addl mat1(,%rdx,4), %eax
# eax = eax + *(mat1 + 4*rdx), similar to above

ret
# return eax
````

Two dimensional arrays in C don't really exist. What an array is is just a long area of contiguous memory. So a two dimensional array is just a very big contiguous array of contiguous arrays. Visually, it can be seen as follows:
`_________ _________ _________ _________` (the blocks are spaced to show them visually, but no gaps exist in memory). If a two dimensional array is declared as `arr[a][b]`, then each block shown above has length `b`, and there are `a` of them in total. In our example, `a` is 4 and `b` is 9. If we wanted to reach an arbitrary index of the array `[x][y]`, then we should go to the `x`th block, and move down a displacement of `y`. This corresponds to a displacement from the beginning of `b*x+y` (as each block is of length `b` and we are moving down `x` of them, and then once we're in the `x`th block, we need to move down `y` more elements to get to the `[x][y]` element).

Therefore for `mat2`, we use the equation `j+11i` to get to any arbitrary point `[i][j]`. Therefore the length of each block is 11, so `M=11`. We apply the same logic to mat1 to get `N=8` (the equation used for mat1 is `j+8i`). The reason for the factor of 4 is that the elements we store are not 1 byte long, but 4 bytes long. So if the first element is at address `0x0`, then the second element is not at address `0x1`, but `0x4`.

Problem 3:
---
````
movl %edi, %eax
# edi is our parameter a
# eax = edi

sall $5, %eax
# eax = eax << 5 (sall is shift arithmetic left long)
# or simply, eax = eax * 2^5 = 32*eax (which holds 32*a)

subl %edi, %eax
# eax = eax - edi
# eax = 32*a - a = 31*a

ret
# return eax (eax = 31*a)
````
Therefore the function is `fun1`.

Problem 4:
---

Problem 5:
---

Problem 6:
---

A.  
`a % 32` gives us the remainder when `a` is divided by 32 (works)  
`a / 32` is integer division by 32 (doesn't work)  
`a >> 5` is just `a / 32`, which we know doesn't work  
`a << 5` is just `a * 32`, which doesn't work  
`a | ~0x1f` `0x1f` is the bit string `0001 1111`. So `~0x1f` is the bit string `1110 0000`. So `a | ~0x1f` is 27 `1` followed by the last 5 bits of a (don't forget about sign extension). This doesn't work  
`a & 0x1f` gives us the last 5 bits of a. This is exactly the remainder when `a` is divided by 32 (works)

B. The best way to solve this one is to set `i` to be some value, and see if the output matches.  
`1 << i` puts a 1 in the `(32-i)`th spot (if the left most spot is defined as spot 1), and 0 everywhere else (doesn't work)  
`(1 << i) - 1` if we let `i` be 5, then `1 << i` is `0000 0000 0000 0000 0000 0000 0010 0000`. Then `(1 << i) - 1` is `0000 0000 0000 0000 0000 0000 0001 1111`. This is an opposite of what we want (right-most `i` bits are 1) (doesn't work)  
`((1 << i) - 1) << (32 - i)` we take what we have above, and given `i` is still 5, this gives us `1111 1000 0000 0000 0000 0000 0000 0000`, which is what we want (works)  
`1 << (32 - i) - 1` be careful on order of operations (shift happens before the subtraction of 1). Let `i` be 27, then `1 << (32 - i)` is `0000 0000 0000 0000 0000 0000 0010 0000`. Then subtracting 1 yields `0000 0000 0000 0000 0000 0000 0001 1111`. This is an opposite of what we want (bits are flipped) (doesn't work)  
`~((1 << (32 - i)) - 1)` this is the negated version of above, which works  
`0xf8000000` this is a constant value. If we let `i` be 32, then we should get a bit string of all `1`, which this is not (doesn't work)

C.
Floats are stored in memory as follows: 1 bit for sign, 8 bits for exponent, and 23 bits for mantissa. If our float is `-2.05`, then the sign bit must be `1`. If we reinterpret this binary form as a signed integer, then the signed integer must be negative. So the answer cannot be `1`, `2`, or `2.05`. If we look at the binary form of the signed integer `-1`, this is the bit string of all `1`. That means if we reinterpret this as a float, then the exponent field is all `1`, which corresponds to `NaN` (not a number). So the answer is not `-1`. For `-2`, the binary form is only changed in the least significant 2 digits, so the exponent field remains all `1`. Then `-2` is also not an answer. Therefore the answer is `none of the above`.

D. Don't forget how pointer arithmetic works
````c
int *p;
char *q;
p = (int *)1;
// this line implies that p holds the address 1
// it does not mean p points to the number 1

p++;
// if p pointed to an integer that was at address 1, and then p is pointing to the next integer, the next integer is located at address 1 + sizeof(int) = 1 + 4 = 5

q = (char *)(p+2);
// p + 2 means the 2nd integer after the current one; if p points to an integer located at address 5, then the 2nd integer after it is at address 13. Then we simply treat this new address as an address that holds a character, so q is 13
````
Therefore the answer is `p = 5, q = 13`.

E.
The swap method is meaningless. The only variables swapped (and they aren't even swapped, the swap is written incorrectly) are the local ones on the stack. Pointers aren't passed into the function, but rather then integers themselves. So whatever happens in the swap is local to the swap function. Then the values remain as they were in the main function. Therefore the answer is `a = 1, b = 2`.
