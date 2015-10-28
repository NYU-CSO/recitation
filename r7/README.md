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
