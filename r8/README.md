Tutorial 8
=========

Git
-----
Git is a version control system. First, watch this video for a quick introduction on what Git is: https://www.youtube.com/watch?v=_Jmkvv_nKTE. Second, sign up for a host that lets you have private repositories (Bitbucket, GitHub, etc). If you are using GitHub, you can sign up for the student pack at https://education.github.com/pack. This guide will assume you're using GitHub.

Let's walk through creating a repository, adding items into it, pushing it onto GitHub, and pulling from GitHub. This exercise is best done with another person (for the pull section).

Create a repository. You should do this step on GitHub, so you can set private access correctly. There is also an option in the repository settings to add collaborators (other people who can read/write to the repository). You will then be given a repository URL (on the right hand side of the screen, called `HTTPS clone URL`) of the form https://github.com/username/repo.git.

Let's first clone this repository onto our local machine. This will create a folder in our current directory called `repo` where the code will reside.
```
stud@lubuntu64~$ git clone https://github.com/user/repo.git
Cloning into 'repo'...
Username for 'https://github.com': user
Password for 'https://user@github.com': ...
warning: You appear to have cloned an empty repository.
Checking connectivity... done.
stud@lubuntu64:~$ cd repo/
stud@lubuntu64:~/repo$ ls
```
You can ignore the warning for an empty repository (we just created it, why should there be anything inside of it? the output from `ls` also says this).

Let's add some code inside of the repository.
```
stud@lubuntu64:~/repo$ touch main.c
```
This creates a blank file called `main.c` that you can then edit with your favorite text editor. After putting some code in there (we wrote hello world), let's then send our code to the GitHub repository. If you open the GitHub repository in the browser, you'll note that there's nothing there, even though on your local machine you have a file called `main.c`.

Let's commit our code (create a "snapshot"). First, look at http://stackoverflow.com/questions/3580802/how-to-use-git-git-config-global. Ignore the question, and look only at the top answer. This answer tells you how to configure Git with your name and email address (needed to push commit code).
```
stud@lubuntu64:~/repo$ git add main.c
stud@lubuntu64:~/repo$ git commit -m "Wrote hello world"
[master (root-commit) f5d84b0] Wrote hello world
 1 file changed, 7 insertions(+)
 create mode 100644 main.c
```
The `-m` flag for `git commit` is followed by a string that contains a commit message. Make these informative so other people can understand what this commit contains. If you refresh the browser, you'll notice there's still nothing on GitHub. That's because we've committed, or "snapshotted" our changes on the local machine, but never pushed them onto GitHub.

Let's push our code to GitHub.
```
stud@lubuntu64:~/repo$ git push origin master
Username for 'https://github.com': user
Password for 'https://user@github.com': ...
Counting objects: 3, done.
Delta compression using up to 2 threads.
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 287 bytes | 0 bytes/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To https://github.com/user/repo.git
 * [new branch]      master -> master
```
The `origin` part is which remote you are pushing to, and the `master` part is the branch. Remotes and branches will not be covered in this section, but you can research them if you wish.

If you refresh your browser now, you will find that there is code on GitHub.

Now, your partner should repeat this exercise with a different file called something else, and push his code. If you refresh your browser, you'll find that both yours and his code is on GitHub, but your local machine still has the older version without his code.

Let's pull the latest version of the code from GitHub.

```
stud@lubuntu64:~/repo$ git pull
Username for 'https://github.com': user
Password for 'https://user@github.com':
remote: Counting objects: 3, done.
remote: Compressing objects: 100% (3/3), done.
remote: Total 3 (delta 0), reused 3 (delta 0), pack-reused 0
Unpacking objects: 100% (3/3), done.
From https://github.com/user/repo
   f5d84b0..bfb9c97  master     -> origin/master
Updating f5d84b0..bfb9c97
Fast-forward
 file.c | 7 +++++++
 1 file changed, 7 insertions(+)
 create mode 100644 file.c
```

Now, your local machine will have the same code you see on GitHub. Be sure to frequently perform `git pull` so that you have the latest version of the code. Occasionally, you will get something called a merge conflict, which is when you have two commits that conflict with each other. Sometimes, Git will be able to automatically fix them, and sometimes you will be explicitly told to fix the merge conflict yourself. This is a scenario where the solution is best learned via research and trial and error.

For a graphical view of the Git repository, you can install the program `gitk` (via `sudo apt-get install gitk`) and run it from the command line within a Git repository.

Compiling code, source files, object files, binaries/executables
------
The general lifecycle (simplified for this exercise) for a C program is: `source code --(compiler)--> object file --(linker)--> executable`. You can only run the executable.  
We use GCC, or GNU Compiler Collection to turn our source code into an executable. We can also give GCC various flags to turn our code into an intermediate step (such as an object file).

Let's go through these 3 steps explicitly using two source files and GCC. These files are `main.c` and `library.c`.

Let's compile each C file into its corresponding object file (.o extension).

```
stud@lubuntu64:~/cso/recitation/r8$ gcc main.c -c -o main.o
stud@lubuntu64:~/cso/recitation/r8$ gcc library.c -c -o library.o
```

If you run `ls`, you'll see that the two object files were created. Let's go over the two flags we used, `-c` and `-o`. `-c` tells GCC that the output should be an object file (rather than the default behavior, an executable). `-o file.o` tells GCC that the output should be called `file.o`.

Now, let's link the two object files together into an executable that we can run.

```
stud@lubuntu64:~/cso/recitation/r8$ gcc main.o library.o -o executable
```

Here, GCC takes in two inputs, the two object files created above. Our output should go to a file called `executable`. No other flags were used, so the default behavior of creating an executable happens. Then we can run our code.

```
stud@lubuntu64:~/cso/recitation/r8$ ./executable
Hello world
```

Now, let's introduce some other flags.  
`-g` enables debugging symbols (so output from GDB/Valgrind makes more sense and includes line numbers)  
`-Wall` gives you warnings  
`-Wextra` gives you even more warnings (use both of them, not just one)  

Let's try out these flags (they should be used when working with source files)
```
stud@lubuntu64:~/cso/recitation/r8$ gcc -g -Wall -Wextra main.c -c -o main.o
main.c: In function ‘main’:
main.c:7:1: warning: control reaches end of non-void function [-Wreturn-type]
 }
 ^
```

We have a compiler warning. It says that the function `main` has a return type that isn't void, but nothing is explicitly returned. If you look at `main.c` lines 6 and 7, you'll see that there is no `return 0;`. Put that in, and rerun the above command.  

```
stud@lubuntu64:~/cso/recitation/r8$ vim main.c
stud@lubuntu64:~/cso/recitation/r8$ gcc -g -Wall -Wextra main.c -c -o main.o
```
Now you'll notice that the compiler is happy. We can repeat this process on `library.c` as well (which produces no warnings/errors), and then create our executable.

```
stud@lubuntu64:~/cso/recitation/r8$ gcc -g -Wall -Wextra library.c -c -o library.o
stud@lubuntu64:~/cso/recitation/r8$ gcc library.o main.o -o executable
```

Note that we didn't bother using the various flags in the command that links the object files together. That's because object files aren't C code, so flags that deal with reading C code are irrelevant.

Debugging memory-related errors (including segmentation faults)
-----

In the above section, we created the file `executable` that prints out "Hello World". No segmentation faults happened. But are we sure that we correctly used functions related the memory, didn't go out of bounds, etc? First, install the program Valgrind (via `sudo apt-get install valgrind`). We will use the Memcheck feature of Valgrind (the default one).

Let's run our executable inside Valgrind.

```
stud@lubuntu64:~/cso/recitation/r8$ valgrind ./executable
==3636== Memcheck, a memory error detector
==3636== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3636== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==3636== Command: ./executable
==3636==
Hello world
==3636==
==3636== HEAP SUMMARY:
==3636==     in use at exit: 13 bytes in 1 blocks
==3636==   total heap usage: 1 allocs, 0 frees, 13 bytes allocated
==3636==
==3636== LEAK SUMMARY:
==3636==    definitely lost: 13 bytes in 1 blocks
==3636==    indirectly lost: 0 bytes in 0 blocks
==3636==      possibly lost: 0 bytes in 0 blocks
==3636==    still reachable: 0 bytes in 0 blocks
==3636==         suppressed: 0 bytes in 0 blocks
==3636== Rerun with --leak-check=full to see details of leaked memory
==3636==
==3636== For counts of detected and suppressed errors, rerun with: -v
==3636== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Let's interpret the output. Lines prefixed with `==num==` is output from Valgrind (where `num` is the process ID). That means that this program produced one line of output `Hello world` (as we expected). But, if you look at the heap and leak summary, we allocated 1 block on the heap of 13 bytes, but freed 0 times. At the end of the program (from the main function), those 13 bytes went out of scope (no variable refers to them, so we can't explicitly free it inside of the main function). Let's rerun with the flag that tells us details about leaked memory (see the above output for that flag). Note that the flag needs to come before your executable name.

```
stud@lubuntu64:~/cso/recitation/r8$ valgrind --leak-check=full ./executable
==3640== Memcheck, a memory error detector
==3640== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3640== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==3640== Command: ./executable
==3640==
Hello world
==3640==
==3640== HEAP SUMMARY:
==3640==     in use at exit: 13 bytes in 1 blocks
==3640==   total heap usage: 1 allocs, 0 frees, 13 bytes allocated
==3640==
==3640== 13 bytes in 1 blocks are definitely lost in loss record 1 of 1
==3640==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==3640==    by 0x400697: print_string (library.c:8)
==3640==    by 0x4006FF: main (main.c:6)
==3640==
==3640== LEAK SUMMARY:
==3640==    definitely lost: 13 bytes in 1 blocks
==3640==    indirectly lost: 0 bytes in 0 blocks
==3640==      possibly lost: 0 bytes in 0 blocks
==3640==    still reachable: 0 bytes in 0 blocks
==3640==         suppressed: 0 bytes in 0 blocks
==3640==
==3640== For counts of detected and suppressed errors, rerun with: -v
==3640== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

It seems that in `library.c` on line 8, we called `malloc`, but we never freed that block. Fix this bug, recompile your code (turn the C file into object file, then link the two object files into an executable), then rerun Valgrind. You should get output similar to the below.

```
stud@lubuntu64:~/cso/recitation/r8$ gcc -g -Wall -Wextra library.c -c -o library.o
stud@lubuntu64:~/cso/recitation/r8$ gcc library.o main.o -o executable
stud@lubuntu64:~/cso/recitation/r8$ valgrind ./executable
==3665== Memcheck, a memory error detector
==3665== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==3665== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==3665== Command: ./executable
==3665==
Hello world
==3665==
==3665== HEAP SUMMARY:
==3665==     in use at exit: 0 bytes in 0 blocks
==3665==   total heap usage: 1 allocs, 1 frees, 13 bytes allocated
==3665==
==3665== All heap blocks were freed -- no leaks are possible
==3665==
==3665== For counts of detected and suppressed errors, rerun with: -v
==3665== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

You'll notice that the program still correctly outputs `Hello world` but now there are no memory-related errors. We freed all blocks we allocated onto the heap.

Let's look at another example, in the file `buggy-code.c`. Compile this into an object file (don't forget about the various flags to give GCC), then into an executable, and figure out what the bug is (hint: there are two). Document what they are, and potential fixes for them.

A third example is in the binary `buggy-executable`. We withhold the source file `buggy-executable.c`. Using GDB and Valgrind, can you figure out what happens, and why? What is a potential fix for this? Can you use GDB to recreate sections of the source code?

Section 9.11 in the textbook (pages 870 to 875) contains a few example of common memory-related bugs in C code.

Types and Typedef
-----

### Types

When coding in C, it's incredibly important to know what the different types are. For each of the following primitive types, be sure you can answer the two questions: what is its size (in bits/bytes)? when would you use it? *The answers should be immediate!*

1. `int`
2. `char`
3. `float`
4. `long long` (vs. `long`)
5. `double`
6. `size_t`
7. `unsigned int`
8. `time_t`

Along these same lines, what would calling `sizeof(VARIABLE)` (equivalent to calling `sizeof(type)`) return?

The values `size_t` and `ssize_t` are typedef'd as `long unsigned int` and `long` respectively. `long unsigned int` is essentially an `unsigned long`. You may have seen these values before, but not known what they meant.

What is the output of the following block of code?
```c
char a[10];
char *b = (char *)malloc(sizeof(int) * 10);

printf("%d %d\n", sizeof(a), sizeof(b));
```

### typedef

In addition to the above types, you also have the ability to define your own types by way of the `typedef` command. Recall that one of the tenets of good code is readability. Consider the following code:

```c
// Returns the length of the string 'name' and
// operates under the assumption 'name' has
// fewer than 128 characters.

char get_length (char * name) {
  char i = 0;
  while (name[i] != NULL) {
    i++;
  }
  return i;
}
```

The above code is fine; however, it's a bit weird that we're storing the length of name in a char. For the sake of efficiency we should be storing values that we *know* to be < 128 in char's, but for the sake of readability, we might want to define a new type, like `name_length`. We could so as below:

```c
typedef char name_length;

name_length get_length (char * name) {
  name_length i = 0;
  while (name[i] != NULL) {
    i++;
  }
  return name_length;
}
```

Cool! Of course, you might ask whether it was *really* necessary to create a whole new type called `name_length` instead of using (e.g.) char ... and this author would agree it isn't strictly preferable. But in general, being able to name your own types can be exceedingly useful for readability and style.

An especially useful place you should feel inclined to use typedefs is whenever you're dealing with structs. Recall a struct allows you to group several primitive variables together into a single unit.

```c
struct node {
  struct node * head;
  struct node * next;
  struct node * prev;
  int value;
}
```

The above defines a simple node structure for a linked list, very similar to what you've used in previous labs. You'll recall that each time you needed a node, you had to type `struct node`. Typedef lets us get around that by typedef'ing the `struct node` to something like `node_t`. See the following:

```c
typedef struct node {
  struct node * head;
  struct node * next;
  struct node * prev;
  int value
} node_t;
```

Complete the following code:

```c
typedef struct node { ... } node_t;
typedef size_t list_size;

node_t find_node ( node_t head , int value ) {
  // YOUR CODE HERE
}

list_size length ( node_t head ) {
  // YOUR CODE HERE
}
```

Note that you cannot use a typedef'd value in its own definition, but you can use values that were completely typedef'd defined above it (as in, in the definition of `node_t`, `head` is of type `struct node *` rather than `node_t *`)

C Preprocessor Macros
-----

First, you should understand the ternary operator. Read https://en.wikipedia.org/wiki/%3F:#C.

````c
int max(int x, int y)
{
  int max = 0;

  max = x > y ? x : y

  // equivalent to
  if (x > y)
  {
    max = x
  }
  else
  {
    max = y
  }
  return max;
}
````

Then read https://en.wikipedia.org/wiki/C_preprocessor#Macro_definition_and_expansion.
The null pointer, or `NULL` is actually the macro `#define NULL ((void *)0)`. The preprocessor goes through your code, finds every instance of the string `NULL`, and replaces it with the string `((void *)0)`. You can also do things like `#define M_PI 3.14159265358979323846` (this is how C actually defines pi in `math.h`). Keep in mind that when you run your code in GDB and use the feature to look at what line of code you're executing, you'll see the actual value `((void *)0)` rather than the word `NULL`. Don't forget the need for parenthesis is because of literal replacement.

Not only can you define objects (such as constants), you can also define quick functions. Above, you saw the logic for getting the maximum of two numbers using a function. You can also write a macro to do this (page 857 of textbook). Let's look at that macro.

````c
#define MAX(x,y) ((x) > (y) ? (x) : (y))
````

We can now use either of the following two statements to do the same thing

````c
int x = 10;
int y = 40;
int maxn = 0;

maxn = max(x, y); // calls the function max
maxn = MAX(x, y); // expands the macro MAX out
````

Suppose we have a bitmap that we defined as

````c
char *bitmap = (char *)malloc(sizeof(char) * 100);
memset(bitmap, 0, sizeof(char) * 100);
````

This means the bitmap has enough space to hold 800 values. Assuming our bitmap is written in Big Endian, can you write a macro that will turn a bit at an index `i` to 1 without affecting the other bits (the recommended way is to do it in one line, but you could call other macros)?

Can you do the same except to extract a bit at an index `i`? The value returned should be 0 or 1.

Various dynamic memory allocation strategies
-----

Section 9.9 in the textbook (pages 839 to 865) contains information on dynamic memory allocation.

Recall that we cannot use any complicated data structure (such as hashtable) that would require dynamic memory allocation (this is a circular/chicken and egg problem, can't implement dynamic memory allocator using dynamic memory).

The following implementations build on top of each other. Start by fully understanding the implicit free list, and move one level at a time.

Section 9.9.6 to 9.9.12 in the textbook (pages 847 to 862) covers the implicit free list strategy (and implements it). Sample code is provided here, and you are allowed to use and modify it for your implementation.

Section 9.9.13 in the textbook (pages 862 to 863) covers the explicit free list strategy.

Section 9.9.14 in the textbook (pages 863 to 865) covers the segmented free list strategy.

If you can think of a better strategy for a dynamic memory allocator, feel free to implement it and try its performance via the grading scripts in the lab.
