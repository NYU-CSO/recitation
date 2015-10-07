Tutorial 4
==========
Exercise 1 -- Understanding assembly and C with GDB
-----

The goal of this exercise is to run and examine the assembly code using GDB to solidify your understanding of C.
```c
long
addone2(long x)
{
	x++;
	return x;
}

long
addone(long *x)
{
	(*x)++;
	return *x;
}

int main()
{
	long x = 1;
	long rx;

	rx = addone2(x);
	printf("x=%ld rx=%ld\n", x, rx);
	 
	rx = addone(&x);
	printf("x=%ld rx=%ld\n", x, rx);

	rx = addone((long *)x);
	printf("x=%ld rx=%ld\n", x, rx);
}
```

Compile the above program (also available as `main.c` in this directory) by typing `gcc -Og -g main.c`.
Next, run gdb by typing `gdb ./a.out`.   Learn to use the following GDB commands:

- `disass <func>` disassembles a given function or memory address. When running `disass` without arguments, it 
disassembles the current function.
- `x/i <address>` prints the content of the address as an assembly instruction.
- `p/x $rax` prints the %rax register. you can print out other registers too. e.g. `p/x $rip`. Yup, use the `$` prefix instead of `%` prefix. It's annoying, i know.
- `info registers` prints out the current values of all registers and the condition codes (see under eflags)
- `nexti` executes the next assembly instruction (`next` executes the next C statement)
- `break <func>` causes the debugger to stop when a given function is entered.

Now, let's walk through an example.
Suppose I want to find out where the `x` variable is stored in the `main` function. 
How do I do that with GDB?

Let's first invoke gdb (assuming ./a.out has already been created with `gcc -Og -g main.c`)
```
$ gdb ./a.out
....
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./a.out...done.
(gdb) 
```

To find out information about the `x` variable in the main function, let's stop the debugger in the main function. To do that, we 
use the `break` command followed by the `run` command.
```
(gdb) b main
Breakpoint 1 at 0x40056d: file main.c, line 17.
(gdb) r
Starting program: /home/jinyang/classes/fa15-cso/recitation/r5/a.out 

Breakpoint 1, main () at main.c:17
17	{
(gdb) 
```

Now, i'm stopped in the first instruction of the `main` function. It's time to find out
those instructions that compose of the `main` function.
```
(gdb) disass
Dump of assembler code for function main:
=> 0x000000000040056d <+0>:	sub    $0x18,%rsp
   0x0000000000400571 <+4>:	movq   $0x1,0x8(%rsp)
   0x000000000040057a <+13>:	mov    $0x1,%edi
   0x000000000040057f <+18>:	callq  0x40055d <addone2>
   ...
```

As we can see in the above output, the next instruction to be executed has an arrow next to it.
And based on the dissembled output, the next instruction is stored at memory address `0x000000000040056d`.
And this should be the value of the %rip register. Let's check that it indeed is 
the case.

```
(gdb) p/x $rip
$1 = 0x40056d
```

Yup. That is exactly what we expect.

It's time to move on. Let's execute the next instruction
```
(gdb) nexti
18		long x = 1;
```

Well, it's not ideal that GDB displays the next C statement to execute when it stops.  What I really want here is for GDB
to display the next assembly instruction to execute.  Fortunately, I can configure GDB to do what I want by
```
(gdb) set disassemble-next-line on
```

Now, I'll restart the program and executes the first assembly instruction of the `main` function again.
```
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/jinyang/classes/fa15-cso/recitation/r5/a.out 

Breakpoint 1, main () at main.c:17
17	{
=> 0x000000000040056d <main+0>:	48 83 ec 18	sub    $0x18,%rsp
(gdb) nexti
18		long x = 1;
=> 0x0000000000400571 <main+4>:	48 c7 44 24 08 01 00 00 00	movq   $0x1,0x8(%rsp)
```

Ok, it looks like my next instruction `movq $0x1,0x8(%rsp)` tries to move constant value `1` into some memory 
location which is the `8` plus the content of register %rsp.  This gives me a reasonable suspicion that 
memory location `0x8(%rsp)` stores variable x, because line 18 of `main.c` initializes x to have value one.

Now let's execute the `movq` instruction and print out the address and content of `0x8(%rsp)`.
```
(gdb) nexti
21		rx = addone2(x);
=> 0x000000000040057a <main+13>:	bf 01 00 00 00	mov    $0x1,%edi
   0x000000000040057f <main+18>:	e8 d9 ff ff ff	callq  0x40055d <addone2>
(gdb) p/x 8+$rsp
$1 = 0x7fffffffdfd8
(gdb) x/8b (8+$rsp)
0x7fffffffdfd8:	1	0	0	0	0	0	0	0
```

So, variable x is stored in memory location `0x7fffffffdfd8`.  We can verify our hypothesize
with other clues as well. 

Now it's time that you roll up the sleeves of your shirt and do some detective work yourself to 
answer the following question
- Where is variable x stored in function `addone2` and `addone`, respectively?
- Which instruction(s) correspond to line 12 in `main.c`?
- Which assembly instruction causes "segmentational fault"? Why?

==========
Exercise 2 -- More C Pointer exercise
-----

Please complete the code as instructed in `exercise2.c`

==========
Exercise 3 -- More Pointer exercise
-----

Please complete the code as instructed in `exercise3.c`

==========
Exercise 4 -- The last C exercise, unless you want more
-----
Please answer the qustions and complete the code as instructed in `exercise4.c`

