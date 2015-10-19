Exercise 1
-----

First, let's get a list of all of the assembly instructions in the binary generated from compiling main.c as follows  
`gcc -g -Og main.c -o a.out`  
`objdump -D a.out > dump.txt`  
Now we have a file that contains the assembly instructions fir the binary, which we can open up in our favorite text editor. You can also use `objdump` to intermix source code and assembly, using the `-S` flag. We will use the `-S` flag (`objdump -S a.out > dump_and_source.txt`).

Now we can run our binary using GDB (instructions on the README). First, let's disassemble on each line of C code with the command `set disassemble-next-line on`. Let's break at the function `addone2` with the command `b addone2`, and run with `r`. We can see where the variable `x` is stored with the command `p &x`, and we see that `x` is stored inside the register `%rdi`. You can also check the value of `x` via `p x` and the register `%rdi` with `i r rdi` (or `info registers rdi`), or `p $rdi` (the syntax for registers differs for which command you use).

````
(gdb) r
Starting program: /home/stud/cso/recitation/r5/a.out

Breakpoint 1, addone2 (x=x@entry=1) at main.c:5
5		x++;
=> 0x000000000040055d <addone2+0>:	48 8d 47 01	lea    0x1(%rdi),%rax
(gdb) print &x
Address requested for identifier "x" which is in register $rdi
(gdb) p $rdi
$1 = 1
(gdb) p x
$2 = 1
(gdb) i r rdi
rdi            0x1	1
````

We can do the same for the function `addone`.

```
(gdb) b addone
Breakpoint 2 at 0x400562: file main.c, line 12.
(gdb) c
Continuing.
x=1 rx=2

Breakpoint 2, addone (x=x@entry=0x7fffffffdfe8) at main.c:12
12		(*x)++;
=> 0x0000000000400562 <addone+0>:	48 8b 07	mov    (%rdi),%rax
   0x0000000000400565 <addone+3>:	48 83 c0 01	add    $0x1,%rax
   0x0000000000400569 <addone+7>:	48 89 07	mov    %rax,(%rdi)
(gdb) p &x
Address requested for identifier "x" which is in register $rdi
(gdb) p x
$3 = (long *) 0x7fffffffdfe8
(gdb) i r rdi
rdi            0x7fffffffdfe8	140737488347112
(gdb) p $rdi
$4 = 140737488347112
(gdb) p /x $rdi
$5 = 0x7fffffffdfe8
(gdb) p *$rdi
$6 = 1
(gdb) p *x
$7 = 1
(gdb)
```
Notice that the line of C `(*x)++;` corresponds to multiple assembly instructions. We can think of it like this: get the value which `x` points to, increment it, and then put it back to where we got it from (which is exactly what the 3 instructions do in that order).

We can break on line 12 to see what instructions we get for the line `(*x)++`, which we just did above.

Can we figure out where the segmentation fault happens? If we just run the program in GDB until the segmentation fault, we can see where it breaks.

```
Program received signal SIGSEGV, Segmentation fault.
addone (x=0x2) at main.c:12
12		(*x)++;
=> 0x0000000000400562 <addone+0>:	48 8b 07	mov    (%rdi),%rax
   0x0000000000400565 <addone+3>:	48 83 c0 01	add    $0x1,%rax
   0x0000000000400569 <addone+7>:	48 89 07	mov    %rax,(%rdi)
```
So the variable `x` holds the value `2`, and `x` is a `long *`. This will clearly led to a segmentation fault when `x` is dereferenced. The specific instruction that does this is the one marked with the arrow: `mov (%rdi),%rax`. Trying to take the value at the address given by register `%rdi`, or trying to dereference `x`, causes the segmentation fault (line 27 of the source code to see the function call).
