Exercise 2
-----

The initial assumption is that we are running out of memory because the program fails at 100,000 nodes. We can open up GDB and run the program with 100,000 times and wait for it to crash again. GDB informs us that we received a `SIGSEGV` (segmentation fault) at line 29, calling the insert method.

We can then use `backtrace -10` to show the last 10 stack frames and notice that we crashed at frame 58,225. We notice that the head pointer jumps from `0x90f438` to `0x7fffffffdfa8` from frame 58,223 to 58,224. We can type `i r rsp` (`info registers rsp`) and notice that the stack pointer is at `0x7fffff7ff000`. We can postulate that we are getting a stack overflow because of how the insert method recursively calls itself.
```
(gdb) r 100000
Starting program: /home/stud/cso/recitation/r6/a.out 100000
successfully inserted 100000 nodes to linked list

Program received signal SIGSEGV, Segmentation fault.
0x000000000040068e in insert (headp=0xad6218, n=0xad6250) at ex2.c:29
29			insert(&head->next, n);
(gdb) bt -10
#58216 0x0000000000400693 in insert (headp=0x90f518, n=0xad6250) at ex2.c:29
#58217 0x0000000000400693 in insert (headp=0x90f4f8, n=0xad6250) at ex2.c:29
#58218 0x0000000000400693 in insert (headp=0x90f4d8, n=0xad6250) at ex2.c:29
#58219 0x0000000000400693 in insert (headp=0x90f4b8, n=0xad6250) at ex2.c:29
#58220 0x0000000000400693 in insert (headp=0x90f498, n=0xad6250) at ex2.c:29
#58221 0x0000000000400693 in insert (headp=0x90f478, n=0xad6250) at ex2.c:29
#58222 0x0000000000400693 in insert (headp=0x90f458, n=0xad6250) at ex2.c:29
#58223 0x0000000000400693 in insert (headp=0x90f438, n=0xad6250) at ex2.c:29
#58224 0x0000000000400693 in insert (headp=0x7fffffffdfa8, n=0xad6250)
    at ex2.c:29
#58225 0x0000000000400786 in main (argc=2, argv=0x7fffffffe0b8) at ex2.c:58
(gdb) i r rsp
rsp            0x7fffff7ff000	0x7fffff7ff000

```

We can set a breakpoint inside the second loop of the main method (`b 57`) and can run the program with an iter value of 60000. We continue 50,000 times (`c 50000`) and then step into the insert function (`si`). Once inside, we notice it is in fact recursing. To confirm our theory, while inside the insert function, we can step 10,000 times (`si 10000`). We are still inside insert. We then continue (`c`) and we're back in the main method. I check the loop variable i (`print i`) and I notice we are only at 50,001. This basically confirms our suspicions. We are recursing so much that we exceed the stack size.
```
(gdb) b 57
Breakpoint 1 at 0x400762: file ex2.c, line 57.
(gdb) r 60000
Starting program: /home/stud/cso/recitation/r6/a.out 60000
successfully inserted 60000 nodes to linked list

Breakpoint 1, main (argc=2, argv=0x7fffffffe0b8) at ex2.c:57
57			n->v = i;
(gdb) c 50000
Will ignore next 49999 crossings of breakpoint 1.  Continuing.

Breakpoint 1, main (argc=2, argv=0x7fffffffe0b8) at ex2.c:57
57			n->v = i;
(gdb) si
0x0000000000400766	57			n->v = i;
(gdb) si 10000
0x000000000040065b	22		}else if (head->v > n->v) {
(gdb) c
Continuing.

Breakpoint 1, main (argc=2, argv=0x7fffffffe0b8) at ex2.c:57
57			n->v = i;
(gdb) p i
$1 = 50001
```

We can then run the command `ulimit -a` and notice that the stack size is `8192KB`. The insert function creates a 100 char array every time, so this will take up 100B. On top of this, we have two arguments that are pointers for every stack frame. This is an additional 2 * 8B = 16B per frame. Inside every function, we also create a new head pointer (head, not to be confused with headp). This is an additional 8B per frame.

So we have a rough guesstimate of `8192 KB/(100B + 16B + 8B) = 66,065`. However, we crash just past 58,000. Did we forget something?

Well, the return address of a function is pushed onto the stack as well. On a 64-bit machine, addresses are 8B. We also need to account for the fact that we will push the previous stack base pointer, so that's another 8B.

So, our answer is `8192 KB/ (100B + 16B + 8B + 16B) = 8192KB/(140B) = 58514`, which is pretty close to our actual 58224 recursive calls.
