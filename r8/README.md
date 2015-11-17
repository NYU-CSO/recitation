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
