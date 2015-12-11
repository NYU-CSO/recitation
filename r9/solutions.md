Tutorial 9 Solutions
=========

Exercise 1: Linking
-----

### Basic Linker knowledge

No error are produced on compiling `list.c`. We compile as `gcc -g -Wall -Wextra -std=c99 -c list.c -o list.o`.

Warnings are produced on compiling `main.c`. We compile as `gcc -g -Wall -Wextra -std=c99 -c main.c -o list.o`.

The first few say that the functions `insert`, `delete`, and `find` are implicitly declared. We should explicitly put function declarations (not implementations) for them along with the `extern` keyword to say that they are implemented in a different file.
The other warnings say that we do not use the command line arguments `int argc` and `char **argv` so we can safely remove them, and instead change the definition for `main` to be `int main()` instead.

Now we can link the two object files `main.o` and `list.o` together to the binary `linkedlist`. Link as `gcc list.o main.o -o linkedlist`.

In the original `list.c` before we fix the output, the linker symbols are:
* `head` weak linker symbol
* `n_inserts` weak linker symbol
* `n_deletes` weak linker symbol
* `insert` strong linker symbol
* `prev` not a linker symbol
* `curr` not a linker symbol
* `malloc` undefined linker symbol
* `delete` strong linker symbol
* `free` undefined linker symbol
* `find` strong linker symbol

In the original `main.c` before we fix the output, the linker symbols are:
* `delete` undefined linker symbol
* `find` undefined linker symbol
* `insert` undefined linker symbol
* `main` strong linker symbol
* `n_deletes` strong linker symbol
* `n_inserts` strong linker symbol
* `printf` undefined linker symbol

In the binary `linkedlist` that we compiled with the original code, the linker symbols are:
* `delete` strong linker symbol
* `find` strong linker symbol
* `free` undefined linker symbol located in GLIBC
* `head` weak linker symbol
* `insert` strong linker symbol
* `main` strong linker symbol
* `malloc` undefined linker symbol located in GLIBC
* `n_deletes` picks the strong linker symbol from `main.c`
* `n_inserts` picks the strong linker symbol from `main.c`
* `printf` undefined linker symbol located in GLIBC

### Linker and Shared library

The shared library we want to look at is located at a machine dependent path, but probably at `/lib/x86_64-linux-gnu/libc.so.6`. If we examine the output from `nm -D`, we see `malloc`, `free`, and `printf` defined in this shared library.

### Programming errors in the linking process

The output is incorrect because there are two definitions for `n_inserts` and `n_deletes`. One is a weak linker symbol, and the other is a strong linker symbol. If we look at the definition for `n_inserts` in `main.c`, we see that is it of type `int` and initialized to `0`. In `list.c`, `n_inserts` is defined as `float` and not initialized. In `main.c`, any operation with `n_inserts` treats the value there as an `int`. In `list.c`, any operation with `n_inserts` treats the value there as a `float`. That means in `list.c` whenever we say `n_inserts++`, a floating point instruction is executed. One solution is to simply change the definition of `n_inserts` and `n_deletes` in `list.c` to type `int`. The better solution is to only have one place where `n_inserts` and `n_deletes` are defined, and everywhere else use the `extern` keyword. Don't forget to recompile and relink, and then we have the output we expect.

Exercise 2: Fork and Exec
-----

There is an error in the function `qsort_cmp`. The return statement should read `return strcmp(*(const char **)a, *(const char **)b);`.

We compile as `gcc -g -Wall -Wextra -std=c99 multisort.c -o sorter`. There are two warnings. One is an unused parameter `char *outfile` in the function `mergewords` (this will be used in the second version of this program), and the other is that `mergewords` returns `int` but there is no return statement. We can't fix the first warning (yet), but the second one can be fixed by adding a return. We will add `return 0;`.

The reason that the contents aren't sorted is because of the fact that when a process (an instance of an executable) calls `fork`, its data (eg stack, heap) is copied verbatim into the child process, but neither process can access the other process's memory.

The parent sorts the first half of the list, and the child sorts the second half of the list. Both store their results in their respective halves, then the child exits. All the work the child did in sorting is not seen in the parent. The parent still has an unsorted second half.

### Fixing Ben's multi-process program

One solution is to write the program in a multi-threaded manner rather than multi-process. This technique will not be covered here.

The other solution is to write out the child's sorted data to a file, let the child exit, and then the parent reads in the sorted data from the file. This is implemented in `multisort-file.c`.

You may notice that we call `malloc` a few times in this program, but never `free`. If you didn't notice this, you should always run your program through Memcheck (via `valgrind`). There is also the caveat that the child has memory that was alloc'd, but exits without freeing it. This also needs to be fixed. You can detect such errors through Memcheck as well with the `--trace-children=yes`, `--leak-check=full`, and `--show-leak-kinds=all` flags. These errors are fixed in `multisort-file.c`.

Feel free to run a diff between the two files to see what changes were made.

### Exec a different program

The algorithm is to have the process fork into a parent and a child. The parent will wait for the child to finish, read in the two input files, and merge them. The child will fork into another parent and child. The child's child will sort the second half of the input file, and the child's parent will sort the first half of the input file, wait for the child's child to finish, and then exit. The reason for this is so that when the original parent waits for its child to finish, the two halves are in the two files (assuming no errors occured).

The solution is implemented in `multisort-exec.c`. Please note that there are memory leaks in the program `sort` that you may see if you run Memcheck on the code. We cannot do anything about this.
