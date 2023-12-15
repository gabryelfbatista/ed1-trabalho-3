#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "utils.h"

#define PAIRS_SIZE 1000

Pair *pair_construct(char *file, int qnt)
{
    Pair *p = malloc(sizeof(Pair));
    p->file = malloc(sizeof(char)*100);
    strcpy(p->file, file);
    p->qnt = qnt;

    return p;
}

void pair_destroy(Pair *p)
{
    free(p->file);
    // free(p);
}


Data *data_construct(char *word)
{
    Data *d = malloc(sizeof(Data));
    d->word = malloc(sizeof(char)*100);
    strcpy(d->word, word);
    d->pairs = hash_table_construct(PAIRS_SIZE, hash_indice, compara_strings);

    return d;
};

void data_add_pair(Data *d, Pair *p)
{
    // Pair *p = pair_construct(file, qnt);
    hash_table_set(d->pairs, p->file, p);
};

Pair *data_get_pair(Data *d, char* file)
{
    Pair *aux = hash_table_get(d->pairs, file);

    return aux;
};


void data_destroy(Data *d)
{
    hash_table_destroy(d->pairs);
    // free(d->word);
    free(d);
}; 

void data_pair_destroy(Data *d, char *file)
{
    Pair *aux = hash_table_get(d->pairs, file);
    if (aux != NULL)
    {
        pair_destroy(aux);
    }
};