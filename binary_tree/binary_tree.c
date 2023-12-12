#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

typedef struct BinaryTreeItem
{
    void *data;
    int key;
    struct BinaryTreeItem *right;
    struct BinaryTreeItem *left;
} BinaryTreeItem;

struct BinaryTree
{
    BinaryTreeItem *root;
    int size;
};

BinaryTreeItem *binary_tree_minimun(BinaryTreeItem *b)
{
    BinaryTreeItem *left = b->left;
    BinaryTreeItem *prev = NULL;
    while(left != NULL)
    {
        prev = left;
        left = left->left;
    }

    return prev;
};

BinaryTreeItem *binary_tree_item_construct(int key, void *data)
{
    BinaryTreeItem *item = (BinaryTreeItem *)calloc(1, sizeof(BinaryTreeItem));
    item->key = key;
    item->data = data;

    return item;
};

BinaryTree *binary_tree_construct()
{
    BinaryTree *b = (BinaryTree *)calloc(1, sizeof(BinaryTree));
    b->root = NULL;
    b->size = 0;
    return b;
};

void binary_tree_set(BinaryTree *b, int key, void *data)
{
    BinaryTreeItem *new_item = binary_tree_item_construct(key, data);

    if (b->root == NULL)
    {
        b->root = new_item;
    }
    else 
    {
        BinaryTreeItem *aux = b->root;
        BinaryTreeItem *prev = NULL;
        while(aux != NULL)
        {
            if (key < aux->key)
            {
                prev = aux;
                aux = aux->left;
            }
            else
            {
                prev = aux;
                aux = aux->right;
            }
        }

        if (key < prev->key)
        {
            prev->left = new_item;
        }
        else 
        {
            prev->right = new_item;
        }

    }

    b->size++;
};

void *binary_tree_get(BinaryTree *b, int key)
{
    BinaryTreeItem *aux = b->root;

    while(key != aux->key)
    {
        if (key < aux->key)
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }
    }

    return aux->data;
};

BinaryTreeItem *get_remove(BinaryTree *b, int key)
{
    BinaryTreeItem *aux = b->root;

    while(key != aux->key)
    {
        if (key < aux->key)
        {
            aux = aux->left;
        }
        else
        {
            aux = aux->right;
        }
    }

    return aux;
};

BinaryTreeItem *get_prev(BinaryTree *b, int key)
{
   BinaryTreeItem *prev = NULL;
   BinaryTreeItem *aux = b->root;

   while(key != aux->key)
    {
        if (key < aux->key)
        {
            prev = aux;
            aux = aux->left;
        }
        else
        {
            prev = aux;
            aux = aux->right;
        }
    }

    return prev;
};

void transplant(BinaryTree *b, BinaryTreeItem* u, BinaryTreeItem *v)
{
    BinaryTreeItem *prev_u = get_prev(b, u->key);
    BinaryTreeItem *prev_v = get_prev(b, v->key);

    if (prev_u == NULL)
    {
        b->root = v;
    }
    else if (u == prev_u->left)
    {
        prev_u->left = v;
    }
    else 
    {
        prev_u->right = v;
    }

    if (v != NULL)
    {
        prev_v = prev_u;
    }
};

void *binary_tree_remove(BinaryTree *b, int key)
{
    BinaryTreeItem *removed_item = get_remove(b, key);

    if (removed_item->left == NULL)
    {
        transplant(b, removed_item, removed_item->right);
    }
    else if (removed_item->right == NULL)
    {
        transplant(b, removed_item, removed_item->left);
    }
    else 
    {
        BinaryTreeItem *minimum = binary_tree_minimun(removed_item->right);

        BinaryTreeItem *prev_minimun = get_prev(b, minimum->key);
        if (prev_minimun->key != removed_item->key)
        {
            transplant(b, minimum, minimum->right);
            minimum->right = removed_item->right;
        }
    }
};

void binary_tree_destroy(BinaryTree *b);