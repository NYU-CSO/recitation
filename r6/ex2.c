#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	long v;
	struct node *next;
}node;

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

int 
main(int argc, char **argv)
{
	if (argc != 2) {
		printf("usage: <number of iteration>\n");
		return 1;
	}
	int iter = atoi(argv[1]);

	//insert iter nodes into a linked list
	node *head = NULL;
	for (int i = iter; i >= 0; i--) {
		node *n = (node *)malloc(sizeof(node));
		n->v = i;
		insert(&head, n);
	}

	printf("successfully inserted %d nodes to linked list\n", iter);	
	

	//insert iter nodes into another linked list
	head = NULL;
	for (int i = 0; i <= iter; i++) {
		node *n = (node *)malloc(sizeof(node));
		n->v = i;
		insert(&head, n);
	}

	printf("successfully inserted %d nodes again to linked list\n", iter);	
	return 0;
}
