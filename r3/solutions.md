Tutorial 3 Solutions
==========

Exercise 1
-----

The solution for this is given in the file `exercise1.c`.

For stringlen, the idea is for every character in the character array, add 1 to a counter, until we reach the end of the string (defined by the null character `'\0'`). We can do this both iteratively (stringlen and stringlen2) and recursively (stringlen3).

For RScase, the idea is for every character in the character array, see if it is a letter. If so, if the letter is the first character in the string, capitalize it, or if the letter is preceded by a space and the letter is not the first character in the string, capitalize it.

Exercise 2
-----

Using the file `exercise2.c`. On line 11, temp is declared to be a pointer to an integer, pointing to the value 0. On line 14, temp is now pointing to count (as in temp = address of count). So `*temp = 20` means set the value of what temp is pointing to to 20. This has the effect of setting count to 20. By the same logic, on line 17, temp is now pointing to sum. So `*temp = count` has the effect of setting sum to what count is, or 20. Then our print statement will print 20, 20, and 20.
