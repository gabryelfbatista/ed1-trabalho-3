#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "forward_list.h"
#include "node.h"


typedef struct
{
    void *key;
    void *val;
}HashTableItem;


void _hash_pair_destroy(HashTableItem *item)
{
    free(item);
}


struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

HashTableItem *hash_item_construct(void *key, void* val)
{
    HashTableItem *h_item = (HashTableItem *)calloc(1, sizeof(HashTableItem));
    h_item->key = key;
    h_item->val = val;

    return h_item;
}

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = calloc(table_size, sizeof(ForwardList *));
    hash_tbl->n_elements=0;

    return hash_tbl;
}

void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = forward_list_get(h->buckets[i], 1);

            while (n != NULL)
            {
                HashTableItem *pair = n->value;
                if (pair != NULL)
                {
                    _hash_pair_destroy(pair);
                }
                n = n->next;
                h->n_elements--;        
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

void hash_table_set(HashTable *h, void *key, void *val)
{
    int key_val = h->hash_fn(h, key);

    if (h->buckets[key_val] == NULL)
    {
        h->buckets[key_val] = forward_list_construct();
    }

    HashTableItem *new_item = hash_item_construct(key, val);
    forward_list_push_front(h->buckets[key_val], new_item);
    h->n_elements++;   
};


void *hash_table_get(HashTable *h, void *key)
{
    int key_val = h->hash_fn(h, key);

    ForwardList *list_aux = h->buckets[key_val];
    HashTableItem *item_aux;

    if (list_aux == NULL)
    {
        return NULL;
    }
    else
    {
        for (int i = 0; i < forward_list_size(list_aux); i++)
        {
            item_aux = forward_list_get(list_aux, i);

            if (h->cmp_fn(item_aux->key, key) == 0)
            {
                return item_aux->val;
            }
        }
    }
    return NULL;
};


int hash_table_size(HashTable *h)
{
    return h->table_size;
};

int hash_n_elements(HashTable *h)
{
    return h->n_elements;
};
