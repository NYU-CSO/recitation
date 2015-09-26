Tutorial 2 Solutions
==========

Exercise 1
-----
1. convert 86 to binary. If we decompose this into powers of two, we get 64 + 16 + 4 + 2, or 2^6 + 2^4 + 2^2 + 2^1, so our binary representation is `0000 0000 0000 0000 0000 0000 0101 0110`.  
In order to convert this to hexadecimal, we note that binary is base 2, and hexadecimal is base 16. So 4 binary digits represent 1 hex digit, and vice versa (which is why the binary is split up into groups of 4). The first 6 groups all represent 0, so our first 6 hex digits are 0, the 7th group is `0101`, or 5 in decimal, which is 5 in hexadecimal. The 8th group is `0110`, or 6 in decimal, which is 6 in hexadecimal. Then our hexadecimal representation is `0x00000056`.
2. convert -94 to binary. Notice how the number is negative, so we first calculate what 94 is and take the 2s complement. Decomposing 94 into powers of two yields 64 + 16 + 8 + 4 + 2, or 2^6 + 2^4 + 2^3 + 2^2 + 2^1, so our binary representation is `0000 0000 0000 0000 0000 0000 0101 1110` (as an aside, converting this to hex, we get `0x0000005e`. Now we take the 2s complement (this involves taking the 1s complement, or flipping each bit, then adding 1). First by flipping each bit we get `1111 1111 1111 1111 1111 1111 1010 0001`, then we add 1 to get `1111 1111 1111 1111 1111 1111 1010 0010}.` Converting to this hex, we get `0xffffffa2`.
3. store these in memory. Recall that x86 processors are little Endian, so the least significant byte gets the lowest address, and a byte is defined as 8 bits, or 2 hex digits. So our memory layout looks as follows (values on top, addresses on bottom):  
`0x56 0x00 0x00 0x00` `0xa2 0xff 0xff 0xff`  
`0x00`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`0x04`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`0x08`
4. add the two numbers. (aside: notice how we're basically doing 86 - 94, but this problem is worded as if we were to do 86 + (-94).) We can straight up add the two numbers in binary (or in hexadecimal).  
&nbsp;&nbsp;&nbsp;&nbsp;`0000 0000 0000 0000 0000 0000 0101 0110`  
`+ 1111 1111 1111 1111 1111 1111 1010 0010`  
`= 1111 1111 1111 1111 1111 1111 1111 1000`  
Or represented in hexadecimal, `0xfffffff8`. Because the first bit of the binary string is 1, we know this must be a negative number. So we must flip the bits and add 1 to "undo" the 2s complement (note how we aren't subtracting a 1) to see what this number is in decimal. We get our flipped binary string to be `0000 0000 0000 0000 0000 0000 0000 0111`, and adding 1 yields `0000 0000 0000 0000 0000 0000 0000 1000`, or `0x00000008`, or 8 in decimal. So we checked that our final answer is -8.
5. store the third value, -8, in memory (values on top, addresses on bottom):  
`0x56 0x00 0x00 0x00` `0xa2 0xff 0xff 0xff` `0xf8 0xff 0xff 0xff`  
`0x00`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`0x04`&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`0x08`

Exercise 2
-----
After calling `f`, nothing happens to `p` and `q`, as the assignment is local to `f`.
After calling `g`, nothing happens to `p` and `q`, as the assignment is local to `f`. In this case, we changed what the pointer `int *p` is pointing to.
After calling `h`, `a` changes to what `b` holds, or `2`. This is because we changed what `a` holds. When we passed in `int *p` to `h`, we passed in the address of `a`. `*p = q` means to change what is at the address of `a` to the value `q`. This means `a` is now `2`.

Exercise 3
-----
At line 04, we have that `a = -64.0 = -1 * 2^6 * 1.000_2`.
Thus:
1. the sign bit should be set = `0b1`
2. the exponent bits should be 133 (= 6+127) = `0b10000101`
3. the mantissa bits should be 0 = 0b0000...0000
Therefore, the bits at &a are
`1 10000101 00000000000000000000000`

It is trivial to compute the binary value of `b`:
`0100 0000 0000 0000 0000 0000 0000 0001`

The addition is standard binary addition,  
&nbsp;&nbsp;&nbsp;&nbsp;`1100 0010 1000 0000 0000 0000 0000 0000`  
`+ 0100 0000 0000 0000 0000 0000 0000 0001`  
`= 0000 0010 1000 0000 0000 0000 0000 0001`  
\+ carry bit

which gives
1. no sign bit set
2. exponent bits as `0b00000101` = 5 => -122 = 5 - 127
3. a very small mantissa `0b0000...0001`  => 2^(-23) = 1.0000001192092896

Together, this forms:
1 \* 2^(-122) \* 1.00000000000000000000001 [base 2]
= 1.8807911855234143 e-37 ... with a carry.

Exercise 4
-----
We need to write the `printb` function. Our first step is to turn the void pointer `void *p` into a pointer to a 4 byte value that we can use.
```c
unsigned int *ptr = (unsigned int *)p;
```
Now that our pointer is in a usable format, we need to print out each bit. We need to figure out how to extract an arbitrary bit at any index, and print it out.

To extract the bit at index `n`, we can shift `*ptr` by `n` to the right. If our original bitstring was `1001110` and we want the bit at index `2`, we do `1001110 >> 2` which returns `10011` (dropping the leading 0s). Now that our desired bit is located at the end of the bitstring, or at index `0`, we can simply `AND`, or `&` with the bitstring `1`, or `0x1`.

Now that we know how to extract a bit at an arbitrary index, we can simply print each bit out via a loop. For the bonus problem, rather than looping through all 32 bits, we need to first loop to find out how many leading 0s we have, and then when looping again for printing, only loop (32 - num leading 0s) times.
