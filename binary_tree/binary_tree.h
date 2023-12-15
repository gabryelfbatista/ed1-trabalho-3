#ifndef _BINARY_TREE_
#define _BINARY_TREE_

typedef int (*CmpFn)(void *, void *);
typedef void (*KeyDestroyFn)(void *);
typedef void (*ValDestroyFn)(void *);

typedef struct BinaryTree BinaryTree;


BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn);

void binary_tree_set(BinaryTree *b, void *key, void *value);

void *binary_tree_get(BinaryTree *b, void* key);

void *binary_tree_remove(BinaryTree *b, int key);

void binary_tree_destroy(BinaryTree *b);

#endif