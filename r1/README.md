# Basic UNIX usage

Most of you are used to interacting with computers and smartphones by GUI and
the touch interface.  As a developer / programmer / advanced user, you
can do your job more efficiently by mastering the commandline interface.  In
UNIX, most of the interesting things you want to do can be accomplished by skillfully combining
various commands.  

Your lab virtual machine is a Linux box.  Your MacOS laptop is based on BSD
UNIX.  Most UNIX commands you learn apply to both, but there are 
variations.

Please read this [ guide on using UNIX commands ](https://github.com/jlevy/the-art-of-command-line).
Below is a short list of the most basic commands you will typically use on a day to day basis:

* `man`
* `ls`
* `cd` `pwd`
* `cp` `mv`
* `grep`
* `less`
* `wc`
* | and >
* `find`
* `ctrl-c`
* `ctrl-z`
* `tar`
* `curl`
* `apt-get install` (This is a Linux-distribution specific command, and hence not available on Mac)
* `apt-cache search` (same as above)

Despite attending this recitation, many times you will have questions about "how do I do this?" 
"is there a command for doing X?".  The answer to all of these questions can usually 
be discovered by Googling.  Click on those Stackoverflow links.  It has many helpful answers.

## In-class exercises

* Using commandline only, download the source code of Nginx web server. The code's URL is at here: http://nginx.org/download/nginx-1.9.2.tar.gz

* Using commandline only, figure out how many C source files there are in Nginx's codebase. C source files have filenames that end of `.c` suffix.

* Using commandline only, find out which C source file contains the `main` function for Nginx.


# Program development on UNIX 

You've probably all learned programming using IDE, which packages up the whole
development process, i.e. writing the code, turning it into something runnable, and
actually running and debugging into one graphically appealing bundle. The UNIX 
people do things differently.  We tend not to use IDE, but rather, we use 
separate tools for each of these development steps. 

## Step 1: The editor (for writing the code)
You *have to* learn to use one editor, `vim` or `emacs`.  I introduce `vim` here because 
that's the editor I use.  `vim` is a text-editor; all the stuff you want to do 
can be typically accomplished without using the mouse. (That is much faster than 
having to click around)

`vim` has two main modes:
* insert mode (whatever you type end up in the file buffer you are editing)
 - to enter insert mode, hit `i`
* normal mode (whatever you type are interpreted as vim commands)
  - to enter normal mode, hit `<ESC`>

Key commands:
* `h` `j` `k` `l` for left, down, up, right. Once you mastered using these keys, it becomes as natural as riding a bicycle.
* `w` to move forward one word at a time, `b` to move backward one word at a time.
*  `x` to delete the character under the cursor. `dw` to delete the current word.  `u` to undo.
* `:set number` to show line numbers. `:set nonumber` to turn it off.
* `:w` to save the buffer into the file.
* `:q` to quit vim. `:wq` to write and quit.

Other readings:
* [Vim keyboard cheatshee](http://vim.rtorr.com/)
* [Getting started with vim](http://www.sitepoint.com/getting-started-vim/)
* [Your problem with vim is that you don't grok vi] (http://stackoverflow.com/questions/1218390/what-is-your-most-productive-shortcut-with-vim/1220118#1220118)

There many useful plug-ins that one can install on top of the basic vim. If you want to be fancy and more productive, try these out:
* [NERDtree] (https://github.com/scrooloose/nerdtree)

## Step 2: Code compilation

You use the C compiler, command `gcc`, to compile your C programs.  `gcc` as well as many key pieces of development software (e.g. the C library, make) have been developed by [GNU](http://www.gnu.org/), so typically people refer to GNU/Linux (Strictly speaking, Linux is just a kernel and not the whole system)

* To compile, type `gcc hello.c`. This generates an executable `a.out`. Execute it by typing `./a.out`
* If you want to compile the program to a different name, `gcc -o hello hello.c`

Typically, we do not directly type `gcc` to compile programs. There are several reasons for why not: 
-The gcc command for large software is very long
- We have to compile many source files individually before combining into a single execuable 
- We need to obey dependencies during compilation. e.g. First compile x, then compile Y (if Y uses X).
- We only want to compile those source files that have changed.  

To address all above problems, we use a classic tool called `make`, developed by GNU. To use `make`, you write 
a Makefile.  The meat of a Makefile consists of a bunch of rules.  Here's what a rule looks like
`target: dependency1 dependency2
         commands`

In this repo, I have a Makefile that compiles foo.c into foo:
`foo: foo.o main.o
	  gcc -o foo foo.o main.o
main.o: main.c
	gcc -c main.c
foo.o: foo.c
	gcc -c foo.c
clean:
	rm -f foo.o foo`	
*Question*  type `make`, what is the order of the commands being run? why? 

To make writing such rules more succinct, you use variables and do [https://www.gnu.org/software/make/manual/html_node/Pattern-Match.html](pattern matching)in Makefile.
- Define variables as `FILES:=file1 file2`, use it later as `$FILES`
There are several important [automatic variables](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html). 
-`$@` (target name)
-`$^` (name of all pre-requisites, i.e. dependencies)
- Pattern-matching using `%` and `*`. As an example, this rule
  `%.b: %.a
       cp  $*.a $*.b`
  This rule copies any file with suffix `.aaa` into another file with the same name except having suffix `.bbb`

*Exercise* Rewrite the given Makefile using pattern matching and variables. Make it as clean and re-usable as possible.

# Other Useful Materials on the Web
