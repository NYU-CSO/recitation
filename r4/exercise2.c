#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct node
{
    int v;
    struct node *left;
    struct node *right;
} node;

//allocate a new tree node and initialize its left/right fields to NULL.
//and initialize its value field to v.
node *
alloc_node(int v)
{
    node *n = (node *)malloc(sizeof(node));
    memset(n, 0, sizeof(node)); //man memset
    n->v = v;
    return n;
}

//insert integer v into its proper position in the binary tree
//it is okay for v to appear more than once.
void
insert(node *n, int v)
{
    if (v < n->v)
    {
        if (n->left == NULL)
        {
            n->left = alloc_node(v);
            return;
        }
        else
        {
            insert(n->left, v);
        }
    }
    else
    {
        if (n->right == NULL)
        {
            // the problem is here, if we want to allocate the right node
            // we should store the return of alloc_node into n->right
            // not into n->left
            n->right = alloc_node(v);
            return;
        }
        else
        {
            // same problem as above here
            insert(n->right, v);
        }
    }
}

//search the binary tree for integer v, if it exists, return 1
//if it does not exist, return 0
int
exists(node *n, int v)
{
    if (!n)
    {
        return 0;
    }

    if (n->v == v)
    {
        return 1;
    }
    else if (v < n->v )
    {
        return exists(n->left, v);
    }
    else
    {
        return exists(n->right, v);
    }
}

void main()
{
    printf("Creating new root node...\n");
    node * root = alloc_node(7);
    if(exists(root,7)) printf("Succesfully made root node!\n");

    printf("Creating new node with value smaller than root...\n");
    insert(root,5);
    if(exists(root,5)) printf("New node succesfully made!\n");
    if(root->left->v == 5) printf("Node correctly inserted as left child!\n");
    else printf("Node incorrectly inserted! Not inserted as left child.\n");

    printf("Creating new node with value larger than root...\n");
    insert(root,9);
    if(exists(root,9)) printf("New node succesfully made!\n");
    if(root->right->v == 9) printf("Node correctly inserted as right child!\n");
    else printf("Node incorrectly inserted! Not inserted as right child.\n");

    printf("Creating left and right children for right child of root\n");
    insert(root,8);
    insert(root,10);
    if(exists(root,8) && exists(root,10)) printf("New nodes succesfully made!\n");
    if(root->right->left->v == 8) printf("New node succesfully inserted as left child of first right child\n");
    else printf("New node incorrectly inserted! Not inserted as left child of first right child\n");

    if(root->right->right->v == 10) printf("New node succesfully inserted as right child of first right child\n");
    else printf("New node incorrectly inserted! Not inserted as right child of first right child\n");

    printf("Creating left and right children for left child of root\n");
    insert(root,4);
    insert(root,6);
    if(exists(root,4) && exists(root,6)) printf("New nodes succesfully made!\n");
    if(root->left->left->v == 4) printf("New node succesfully inserted as left child of first left child\n");
    else printf("New node incorrectly inserted! Not inserted as left child of first left child\n");

    if(root->left->right->v == 6) printf("New node succesfully inserted as right child of first left child\n");
    else printf("New node incorrectly inserted! Not inserted as right child of first left child\n");
}
