#include <stdlib.h>
#include "list.h"

node_t *head;

float n_inserts;
float n_deletes;

void
insert(int v)
{
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->val = v;
	n->next = head;
	head = n;
	n_inserts++;
}

void
delete(int v)
{

	node_t *prev = NULL;
	node_t *curr = head;
	while (curr) {
		if (curr->val == v) 
			break;
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
	free(curr);
	n_deletes++;
}

int
find(int v)
{
	node_t *curr = head;
	while (curr) {
		if (curr->val == v)
			return 1;
		curr = curr->next;
	}
	return 0;
}


