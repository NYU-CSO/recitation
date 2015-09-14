# Computer Systems Organization: Tutorial 1 solutions

- [Basic Unix Usage](#basic-unix-usage)
- [Program development](#program-development)
- [Compiling and debugging](#compiling-and-debugging)
- [Git](#git)

Most of these exercises have multiple ways to solve them.

# Basic Unix usage

* `wget http://nginx.org/download/nginx-1.9.2.tar.gz` or `curl -O http://nginx.org/download/nginx-1.9.2.tar.gz`  
(to issue the curl command, you must install curl, doing `sudo apt-get install curl` (which will prompt you for your password))  
Once the file is downloaded, you can extract it.  
`tar -xvf nginx-1.9.2.tar.gz`
* `find nginx-1.9.2/ -name "*.c" | wc -l` or `find nginx-1.9.2/ | grep "\.c$" | wc -l`  
(Note, the -name flag for find and the grep command take in slightly different inputs. The `\.` means look for the `.` character as `.` means "any character", and `$` means end of string.)
* `grep -r "main" nginx-1.9.2`  
The above does not work, as we are searching for the string "main" anywhere in the contents of the file. To look specifically for the function "main", one way to do is to search for "main("  
`grep -r "main(" nginx-1.9.2`  
This command will return you a list of files and the line where the string "main(" was found. Which file do you think contains the primary `main` function for the Nginx web server?
* First we have to find out where the nginx.c file is located. The above command can answer that question implicitly, but a direct command would also work.  
`find nginx-1.9.2/ -name "nginx.c"`  
Now that we have the full path of the nginx.c file, we can then issue the wc command
`wc -l nginx-1.9.2/src/core/nginx.c`
* We can use the `mv` command. We can create a file called `file.txt` using `touch`.  
`touch file.txt`  
`mv file.txt new_name.txt`  
`mkdir subdirectory`  
`mv new_name.txt subdirectory/` moves `new_name.txt` to the sub folder without renaming it  
`mv subdirectory/new_name.txt subdirectory/another_new_name.txt`  
The end result is `file.txt` is now called `another_new_name.txt` in the directory (folder) `subdirectory`

# Program development

* The code for two versions of hello world is given in the `hello_world` folder. You can copy and paste on the terminal by using the right-click menu. Paste in your editor of choice (if vim, be sure to enable insert mode).

# Compiling and debugging

* For the main.o and foo.o commands, add the `-g` flag to the gdb call.

Example:

```
foo.o : foo.c
    gcc -g -c foo.c
```
* After the foo binary is compiled with debugging enabled, run gdb with `gdb foo`
To start running the foo binary, type `run`.
To set a breakpoint, type `b file.c:5` where file.c is a source code file, and 5 is the line to break at.
To view a snippet of the source code, type `l`.
To continue execution until the next breakpoint, type `c`.
To continue execution until the next line of code, type `n`.
With this information, we see that the program continuously executes lines 6 and 7, which are the lines for the condition of a while loop, and its body. We can example the contents of `sum` and `i` per iteration by doing `print i` or `print sum`. We notice that every iteration, `sum` is incremented by 1, and `i` stays constant. With this knowledge, we see that the variable `i` is never incremented, so our loop executes forever. To fix this bug, we simply add the line `i++;`.
* `gcc -g hello_world.c -o hello_world`

# Git

* `git add hello_world.c`  
`git commit -m "Added hello world file"`  
(if you are using a private git repository, you can also push your changes to the remote repository with `git push origin master`)
