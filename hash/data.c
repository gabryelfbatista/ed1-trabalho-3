#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


typedef struct Pair
{
    char *file;
    int qnt;
} Pair;

Pair *pair_construct(char *file, int qnt)
{
    Pair *p = (Pair *)calloc(1, sizeof(Pair));
    p->file = strdup(file);
    p->qnt = qnt;

    return p;
}

void pair_destroy(Pair *p)
{
    free(p);
}

Data *data_construct(char *word)
{
    Data *d = (Data *)calloc(1, sizeof(Data));
    d->word = word;
    d->pairs = vector_construct();

    return d;
};

void data_add_pair(Data *d, char *file, int qnt)
{
    Pair *p = pair_construct(file, qnt);
    vector_push_back(d->pairs, p);
};


void data_destroy(Data *d)
{
    for (int i = 0; i < vector_size(d->pairs); i++)
    {
        Pair *aux = vector_get(d->pairs, i);
        free(aux->file);
        pair_destroy(aux);
    }
    vector_destroy(d->pairs);
    free(d->word);
    free(d);
}; 