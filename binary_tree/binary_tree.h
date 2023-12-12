#ifndef _BINARY_TREE_
#define _BINARY_TREE_

typedef struct BinaryTree BinaryTree;


BinaryTree *binary_tree_construct();

void binary_tree_set(BinaryTree *b, int key, void *data);

void *binary_tree_get(BinaryTree *b, int key);

void *binary_tree_remove(BinaryTree *b, int key);

void binary_tree_destroy(BinaryTree *b);

#endif