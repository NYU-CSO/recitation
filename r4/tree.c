#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct node {
	int v;
	struct node *left;
	struct node *right;
} node;

//allocate a new tree node and initialize its left/right fields to NULL.
//and initialize its value field to v.
node *
alloc_node(int v) {
	node *n = (node *)malloc(sizeof(node));
	memset(n, 0, sizeof(node)); //man memset
 	n->v = v;
	return n;
}

//insert integer v into its proper position in the binary tree
//it is okay for v to appear more than once.
void
insert(node *n, int v) {
	if (v < n->v) {
		if (n->left == NULL) {
			n->left = alloc_node(v);
			return;
		}else{
			insert(n->left, v);
		}
	} else {
		if (n->right == NULL) {
			n->left = alloc_node(v);
			return;
		}else{
			insert(n->left, v);
		}
	}
}

//search the binary tree for integer v, if it exists, return 1
//if it does not exist, return 0
int
exists(node *n, int v) {
	if (!n) {
		return 0;
	}

	if (n->v == v) {
		return 1;
	}else if (v < n->v ) {
		return exists(n->left, v);
	}else {
		return exists(n->right, v);
	}
}


