# Basic UNIX usage

Most of you are used to interacting with computers and smartphones by GUI and
the touch interface.  As a developer / programmer / hacker / advanced user, you
can do your job more efficient by mastering the commandline interface.  In
UNIX, most of the interesting things you do occur by using and combining
various commands.  

Your lab virtual machine is a Linux box.  Your MacOS laptop is based on BSD
UNIX.  So the UNIX commands you learn apply to both mostly identically but have 
some small variations.

Please read this [ guide on using UNIX commands ](https://github.com/jlevy/the-art-of-command-line).
Below is a short list of the most basic commands you will typically use on a day to day basis:

* `man`
* `ls`
* `cd`
* `pwd`
* `grep`
* `less`
* `wc`
* | and >
* `find`
* `ctrl-c`
* `ctrl-z`
* `tar`
* `curl`
* `apt-get install` (Not on Mac)
* `apt-cache search` (Not on Mac)

Despite attending this recitation, many times you will have questions about ``how do I do this?" 
"is there a command for doing X?".  The answer to all of these questions can usually 
be answered by Googling.  Stackoverflow has many helpful answers.

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
* `h` `j` `k` `l` for left, down, up, right. Once you mastered using these keys, it almost becomes as natural as riding a bicycle.
* 

# Other Useful Materials on the Web
