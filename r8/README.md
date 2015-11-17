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
