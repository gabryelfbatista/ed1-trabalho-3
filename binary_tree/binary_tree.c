#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"

typedef struct
{
    void *key;
    void *value;
} KeyValPair;

typedef struct Node
{
    KeyValPair *key_val;
    struct Node *right;
    struct Node *left;
} Node;

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

Node *binary_tree_minimun(Node *b)
{
    Node *left = b->left;
    Node *prev = NULL;
    while(left != NULL)
    {
        prev = left;
        left = left->left;
    }

    return prev;
};

KeyValPair *key_val_pair_construct(void *key, void *value)
{
    KeyValPair *key_val = calloc(1, sizeof(KeyValPair));

    key_val->key = key;
    key_val->value = value;

    return key_val;
};

void key_val_pair_destroy(KeyValPair *key_val)
{
    free(key_val);
}

Node *node_construct(void* key, void *value, Node *left, Node* right)
{
    Node *node = calloc(1, sizeof(Node));

    node->key_val = key_val_pair_construct(key, value);
    node->left = left;
    node->right = right;

    return node;
};

void node_destroy(Node *node)
{
    free(node);
}

BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn, ValDestroyFn val_destroy_fn)
{
    BinaryTree *b = calloc(1, sizeof(BinaryTree));
    b->root = NULL;
    b->cmp_fn = cmp_fn;
    b->key_destroy_fn = key_destroy_fn;
    b->val_destroy_fn = val_destroy_fn;
    return b;
};

void binary_tree_set(BinaryTree *b, void *key, void *value)
{
    Node* new_node = node_construct(key, value, NULL, NULL);
    Node *aux = b->root;
    Node *prev = NULL;

    if (b->root == NULL)
    {
        b->root = new_node;
    }
    else 
    {
        while (aux != NULL)
        {
            if (b->cmp_fn(key, aux->key_val->key) < 0)
            {
                prev = aux;
                aux = aux->left;
            }
            else if(b->cmp_fn(key, aux->key_val->key) > 0)
            {
                prev = aux;
                aux = aux->right;
            }
            else 
            {
                prev = aux;
                break;
            }
        }

        if (b->cmp_fn(key, prev->key_val->key) < 0)
        {
            prev->left = new_node;
        }
        else if (b->cmp_fn(key, prev->key_val->key) > 0)
        {
            prev->right = new_node;
        }
        else 
        {
            b->val_destroy_fn(prev->key_val->value);
            key_val_pair_destroy(prev->key_val);
            prev->key_val = new_node->key_val;
            node_destroy(new_node);
        }

    }

};

void *binary_tree_get(BinaryTree *b, void *key)
{
    Node *aux = b->root;

    if (aux != NULL)
    {
        while(aux != NULL)
        {
            if (b->cmp_fn(key, aux->key_val->key) == 0)
            {
                return aux->key_val->value;
            }
            else if (b->cmp_fn(key, aux->key_val->key) < 0)
            {
                aux = aux->left;
            }
            else
            {
                aux = aux->right;
            }
        }
    }
    return NULL;
};

void _destroy_node_recursive(Node *node)
{
    if (node == NULL)
        return;

    _destroy_node_recursive(node->left);
    _destroy_node_recursive(node->right);

    key_val_pair_destroy(node->key_val);
    node_destroy(node);
}

void binary_tree_destroy(BinaryTree *bt)
{
    _destroy_node_recursive(bt->root);
    free(bt);
}