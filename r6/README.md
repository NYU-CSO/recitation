Tutorial 6
==========
Exercise 1 -- Where are my local variables?
-----
```c
#include <stdio.h>
#include <stdlib.h>

char *
get_str1()
{
	char str[20] = "hello world";
	return str;
}

char *
get_str2()
{
	static char str[20] = "hello world";
	return str;
}

char *
get_str3()
{
	char *str = "hello world";
	return str;
}

char *
get_str4()
{
	char *dst = (char *)malloc(sizeof(100));
	char *src = "hello world";
	for (int i = 0; i < 12; i++) {
		dst[i] = src[i];
	}
	return dst;
}

void main() {

	char *s1, *s2, *s3, *s4;
	s1 = get_str1();
	s2 = get_str2();
	s3 = get_str3();
	s4 = get_str4();

	printf("s1=%s s2=%s s3=%s s4=%s\n", s1, s2, s3, s4);

}

```

Compile the above program (also available as `ex1.c` in this directory) by typing 
```
$ gcc -std=c99 -g -fno-stack-protector -fomit-frame-pointer ex1.c
```
Ignore the gcc warnings.  Run `./a.out`. Can you explain the output?

Now, use gdb in your detective work and answer the following questions:
- What is the _value_ of `str` in the four functions `get_str1` `get_str2` `get_str3` `get_str4`, respectively?
- How does the character buffer `str` become initialized with "hello world" in each of the four functions? 

==========
Exercise 2 -- Down the recursive rabbit hole
-----

Read the C program in `ex2.c`.  The function `insert` inserts a node into the linked list such that 
the overall linked list is sorted in ascending order.
```c
//insert node n into the (ascending) sorted linked list 
// whose head pointer is pointed to by headp
void
insert(node **headp, node *n)
{
	char buf[100];
	node *head = *headp;
	//if head is null, make n the new head
	if (!head) { 
		n->next = NULL;
		*headp = n;

	//if head's value is bigger than n, insert n in front of head 
	}else if (head->v > n->v) { 
		n->next = head;
		*headp = n;
	
	//if head's value is smaller than n, recurse
	}else { 
		
		insert(&head->next, n);
	}
}
```

The `main` function inserts `iter` number of nodes into a linked list in _two_ ways (corresponding to 
the two `for` loop code blocks)

```c
int 
main(int argc, char **argv)
{
	...
	//insert iter nodes into a linked list
	node *head = NULL;
	for (int i = iter; i >= 0; i--) {
		node *n = (node *)malloc(sizeof(node));
		n->v = i;
		insert(&head, n);
	}
	...
	//insert iter nodes into another linked list
	head = NULL;
	for (int i = 0; i <= iter; i++) {
		node *n = (node *)malloc(sizeof(node));
		n->v = i;
		insert(&head, n);
	}
	...
}
```

Compile and run the program by typing 
```
$ gcc  -std=c99 -g -fno-stack-protector -fomit-frame-pointer ex2.c
```
Now run the program and insert different number of nodes into the linked list.
```
$ ./a.out 10
successfully inserted 10 nodes to linked list
successfully inserted 10 nodes again to linked list
$ ./a.out 1000
successfully inserted 1000 nodes to linked list
successfully inserted 1000 nodes again to linked list
$ ./a.out 100000
successfully inserted 100000 nodes to linked list
Segmentation fault

```

Answer the following questions, using gdb.
- Please explain this output.  Which instruction cause the program to incur a segmentation fault? Why?
- Calculate the size of each stack frame. Run the command `ulimit -a` to figure out the stack size limit. Using some back-of-the-envelope-calculation, what is the smallest `iter` that you would expect the program to encounter a segmentation fault?  Does the actual execution match your calculation?

