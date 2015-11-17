
# Exercise 1 Linking

### Basic Linker knowledge

The `list.c` file in this directory implements a simple linked list. Compile this file using command `gcc -std=gnu99 list.c`. Explain the errors produced.  Fix them to produce the object file `list.o`

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

We can examine the shared library to be loaded with `./a.out` using the UNIX tool `ldd` (do `man ldd`).
Type `ldd ./a.out` and find out the pathname of the shared library file that
correspond to C standard library.

Now, let's examine the symbols defined in the C library to see if the remaining undefined symbols of  
`./a.out` can indeed be found there. Type `nm -D <filename>` to list dynamic symbols.  Did you find what you are looking for?


### Programming errors in the linking process

Now let's turn our attention to the actual output of `./a.out`.  The program inserts 100 linked list nodes and then deletes half of them.  Explain why the output statistics are so out of whack. Fix the errors.


# Exercise 2: Fork and Exec

Ben Bitdiddle's boss asks him to sort a file `biblewords.txt` included in this directory. After 
attending last week's lecture, Ben decides to speed up the sorting process by having multiple 
processes simultaneously sort the file.  Ben's machine has many cores, so
spawning multiple processes allows multiple CPU cores to be utilized for
sorting.

Ben's program, `multisort.c`, is included in this directory. Compile and run it to sort the words in 
file `testwords.txt` as follows:

```
$ gcc -std=gnu99 -g multisort.c
$ ./a.out testwords.txt > out
```

Please explain why the content of the output file `out` does not appear to be sorted as expected.

### Fixing Ben's multi-process program

One way to fix Ben's program is to pass data/results between different processes using the file system.One process can create files that are later read by another process. Fix Ben's `multisort.c` program using this general idea.  Test it using the small words file `testwords.txt`. Also test it using the large words file `biblewords.txt`.

### Exec a different program
Create a different multi-process sort program called `multisort2.c` which invokes the binary program `sort` to sort the words instead of implementing our own sort facility using `qsort`. Type `man sort` to see how to use `sort`. Specifically you'll need the `-n` option to sort lines alphabetically.

Hint: You can manually split the input file into two files each containing half of the words in the original file and pass in the names of these split files when invoking your program. Each process can then sort different split files.

Hint: You still need to invoke the `mergewords` function to merge the two sorted intermediate files.
