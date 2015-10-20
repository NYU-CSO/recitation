Exercise 1
-----

Let's take a look at each function, and set a breakpoint right before the return, and printed out the address of `str[0]`.

`get_str1()`
```
(gdb) p str
$1 = "hello world\000\000\000\000\000\000\000\000"
(gdb) p &str[0]
$2 = 0x7fffffffdf98 "hello world"
```

`get_str2()`
```
(gdb) p str
$3 = "hello world\000\000\000\000\000\000\000\000"
(gdb) p &str[0]
$4 = 0x601050 <str> "hello world"
```

`get_str3()`
```
(gdb) p str
$5 = 0x400714 "hello world"
(gdb) p &str[0]
$6 = 0x400714 "hello world"
```

`get_str4()`
```
(gdb) p dst
$7 = 0x602010 "hello world"
(gdb) p &dst[0]
$8 = 0x602010 "hello world"
```

If we try the following command
```
(gdb) info proc mappings
process 6471
Mapped address spaces:

          Start Addr           End Addr       Size     Offset objfile
            0x400000           0x401000     0x1000        0x0 /home/stud/cso/recitation/r6/a.out
            0x600000           0x601000     0x1000        0x0 /home/stud/cso/recitation/r6/a.out
            0x601000           0x602000     0x1000     0x1000 /home/stud/cso/recitation/r6/a.out
            0x602000           0x623000    0x21000        0x0 [heap]
      0x7ffff7a15000     0x7ffff7bd0000   0x1bb000        0x0 /lib/x86_64-linux-gnu/libc-2.19.so
      0x7ffff7bd0000     0x7ffff7dcf000   0x1ff000   0x1bb000 /lib/x86_64-linux-gnu/libc-2.19.so
      0x7ffff7dcf000     0x7ffff7dd3000     0x4000   0x1ba000 /lib/x86_64-linux-gnu/libc-2.19.so
      0x7ffff7dd3000     0x7ffff7dd5000     0x2000   0x1be000 /lib/x86_64-linux-gnu/libc-2.19.so
      0x7ffff7dd5000     0x7ffff7dda000     0x5000        0x0
      0x7ffff7dda000     0x7ffff7dfd000    0x23000        0x0 /lib/x86_64-linux-gnu/ld-2.19.so
      0x7ffff7fe4000     0x7ffff7fe7000     0x3000        0x0
      0x7ffff7ff8000     0x7ffff7ffa000     0x2000        0x0
      0x7ffff7ffa000     0x7ffff7ffc000     0x2000        0x0 [vdso]
      0x7ffff7ffc000     0x7ffff7ffd000     0x1000    0x22000 /lib/x86_64-linux-gnu/ld-2.19.so
      0x7ffff7ffd000     0x7ffff7ffe000     0x1000    0x23000 /lib/x86_64-linux-gnu/ld-2.19.so
      0x7ffff7ffe000     0x7ffff7fff000     0x1000        0x0
      0x7ffffffde000     0x7ffffffff000    0x21000        0x0 [stack]
  0xffffffffff600000 0xffffffffff601000     0x1000        0x0 [vsyscall]
````
This shows us what gets stored where in memory.

In function 1, the string is stored in the stack.  
In function 2, the string is stored in some weird unknown section (address `0x601050`).  
In function 3, the string is stored in a different weird unknown section (address `0x400714`).  
In function 4, the string is stored in the heap.

We can then try the following command
```
(gdb) info files
Symbols from "/home/stud/cso/recitation/r6/a.out".
Unix child process:
	Using the running image of child process 6471.
	While running this, GDB does not access memory from...
Local exec file:
	`/home/stud/cso/recitation/r6/a.out', file type elf64-x86-64.
	Entry point: 0x400490
	0x0000000000400238 - 0x0000000000400254 is .interp
	0x0000000000400254 - 0x0000000000400274 is .note.ABI-tag
	0x0000000000400274 - 0x0000000000400298 is .note.gnu.build-id
	0x0000000000400298 - 0x00000000004002b4 is .gnu.hash
	0x00000000004002b8 - 0x0000000000400330 is .dynsym
	0x0000000000400330 - 0x0000000000400376 is .dynstr
	0x0000000000400376 - 0x0000000000400380 is .gnu.version
	0x0000000000400380 - 0x00000000004003a0 is .gnu.version_r
	0x00000000004003a0 - 0x00000000004003b8 is .rela.dyn
	0x00000000004003b8 - 0x0000000000400418 is .rela.plt
	0x0000000000400418 - 0x0000000000400432 is .init
	0x0000000000400440 - 0x0000000000400490 is .plt
	0x0000000000400490 - 0x0000000000400702 is .text
	0x0000000000400704 - 0x000000000040070d is .fini
	0x0000000000400710 - 0x0000000000400739 is .rodata
	0x000000000040073c - 0x0000000000400790 is .eh_frame_hdr
	0x0000000000400790 - 0x00000000004008dc is .eh_frame
	0x0000000000600e10 - 0x0000000000600e18 is .init_array
	0x0000000000600e18 - 0x0000000000600e20 is .fini_array
	0x0000000000600e20 - 0x0000000000600e28 is .jcr
	0x0000000000600e28 - 0x0000000000600ff8 is .dynamic
	0x0000000000600ff8 - 0x0000000000601000 is .got
	0x0000000000601000 - 0x0000000000601038 is .got.plt
	0x0000000000601040 - 0x0000000000601064 is .data
	0x0000000000601064 - 0x0000000000601068 is .bss
	0x00007ffff7dda1c8 - 0x00007ffff7dda1ec is .note.gnu.build-id in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda1f0 - 0x00007ffff7dda2ac is .hash in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda2b0 - 0x00007ffff7dda38c is .gnu.hash in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda390 - 0x00007ffff7dda630 is .dynsym in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda630 - 0x00007ffff7dda7c4 is .dynstr in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda7c4 - 0x00007ffff7dda7fc is .gnu.version in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda800 - 0x00007ffff7dda8a4 is .gnu.version_d in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda8a8 - 0x00007ffff7dda9e0 is .rela.dyn in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7dda9e0 - 0x00007ffff7ddaa70 is .rela.plt in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ddaa70 - 0x00007ffff7ddaae0 is .plt in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ddaae0 - 0x00007ffff7df54e0 is .text in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7df54e0 - 0x00007ffff7df97e0 is .rodata in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7df97e0 - 0x00007ffff7df9e1c is .eh_frame_hdr in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7df9e20 - 0x00007ffff7dfc178 is .eh_frame in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ffcc00 - 0x00007ffff7ffce6c is .data.rel.ro in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ffce70 - 0x00007ffff7ffcfe0 is .dynamic in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ffcfe0 - 0x00007ffff7ffcff8 is .got in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ffd000 - 0x00007ffff7ffd048 is .got.plt in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ffd060 - 0x00007ffff7ffdfe4 is .data in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7ffe000 - 0x00007ffff7ffe1c8 is .bss in /lib64/ld-linux-x86-64.so.2
	0x00007ffff7a15270 - 0x00007ffff7a15294 is .note.gnu.build-id in /lib/x86_64-linux-gnu/libc.so.6
	0x00007ffff7a15294 - 0x00007ffff7a152b4 is .note.ABI-tag in /lib/x86_64-linux-gnu/libc.so.6
	0x00007ffff7a152b8 - 0x00007ffff7a18d24 is .gnu.hash in /lib/x86_64-linux-gnu/libc.so.6
```
Let's look at address `0x601050`. This is in the data segment (`.data`).  
Let's look at address `0x400714`. This is in the read-only data segment (`.rodata`).

Now we know where all of our variables are stored.  
Why is the string from `get_str1()` the only one overwritten? That's because it's stored on the stack, and after the function `get_str1()` unwinds, that area of the stack is considered inaccessible; we should treat the data now there as garbage. When the other functions start, that area of the stack will be used and overwritten. The other three strings are stored in areas of memory that will not be overwritten (unless done explicitly).
