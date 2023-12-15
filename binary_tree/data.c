#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "utils.h"
#include "binary_tree.h"


Pair *pair_construct(char *file, int qnt)
{
    Pair *p = malloc(sizeof(Pair));
    p->file = malloc(sizeof(char)*100);
    strcpy(p->file, file);
    p->qnt = qnt;

    return p;
}

void pair_destroy(void *p)
{
    Pair *aux = p;
    free(aux->file);
    // free(p);
}


Data *data_construct(char *word)
{
    Data *d = malloc(sizeof(Data));
    d->word = malloc(sizeof(char)*100);
    strcpy(d->word, word);
    d->pairs = binary_tree_construct(compara_strings, key_destroy, pair_destroy);

    return d;
};

void data_add_pair(Data *d, Pair *p)
{
    // Pair *p = pair_construct(file, qnt);
    binary_tree_set(d->pairs, p->file, p);
};

Pair *data_get_pair(Data *d, char* file)
{
    Pair *aux = binary_tree_get(d->pairs, file);

    return aux;
};


void data_destroy(void *data)
{
    Data *d = data;
    binary_tree_destroy(d->pairs);
    // free(d->word);
    free(d);
}; 

void data_pair_destroy(Data *d, char *file)
{
    Pair *aux = binary_tree_get(d->pairs, file);
    if (aux != NULL)
    {
        pair_destroy(aux);
    }
};