
# Exercise 1

### Basic Linker knowledge

The `list` file implements a minimal linked list. compile the `list.c` file included in this directory using command `gcc -std=gnu99 list.c`. Explain the errors produced.  Fix them to produce the object file `list.o`

Compile the `main.c` file included in this directory using command `gcc -std=gnu99 main.c`.
Explain the errors produced. Fix them to produce the object file `main.o`.
Finally, type the command to obtain the binary executable `./a.out`

Among the collection of names
in `list.c` (as shown below), which are linker symbols and which are not? Which linker
symbols are defined in `list.c` and which ones are not?
* `head`
* `n_inserts`
* `n_deletes`
* `insert`
* `prev`
* `curr`
* `malloc`
* `delete`
* `free`
* `find`

After you've answered the above question using sheer brainpower, let's find out the actual answer 
using the UNIX tool called `nm`. Run `nm list.o`. Read the man pages of `nm` (type `man nm`). 
And explain the nm output.  What are the symbols defined? What are the ones undefined? Then, run `nm main.o` and explain its output as well.

Lastly, run `nm ./a.out`. Which previously undefined symbols have now become defined? What are the remaining undefined symbols? What do these remaining undefined symbols correspond to?

### Linker and Shared library

We examine the shared library to be loaded with `./a.out` using the UNIX tool `ldd` (do `man ldd`).
Type `ldd ./a.out` and find out the pathname of the shared library file that
correspond to C standard library.

Now, let's examine the symbols defined in the C library to see if the remaining undefined symbols in 
`./a.out` can indeed be found there. Type `nm -D <filename>` to list dynamic symbols.


### Programming errors in the linking process

Now let's turn our attention to the actual output of `./a.out`.  The program inserts 100 linked list nodes and then deletes half of them.  Explain why the output statistics are so out of whack. Fix the errors.
