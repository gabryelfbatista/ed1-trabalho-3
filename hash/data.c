#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "utils.h"


Pair *pair_construct(char *file, int qnt)
{
    Pair *p = (Pair *)malloc(sizeof(Pair));
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
    d->pairs = hash_table_construct(10, hash_indice, compara_strings);

    return d;
};

void data_add_pair(Data *d, char *file, int qnt)
{
    Pair *p = pair_construct(file, qnt);
    hash_table_set(d->pairs, p->file, p);
};

Pair *data_get_pair(Data *d, char* file)
{
    Pair *aux = hash_table_get(d->pairs, file);

    return aux;
};


// void data_destroy(Data *d)
// {
//     for (int i = 0; i < vector_size(d->pairs); i++)
//     {
//         Pair *aux = vector_get(d->pairs, i);
//         free(aux->file);
//         pair_destroy(aux);
//     }
//     vector_destroy(d->pairs);
//     free(d->word);
//     free(d);
// }; 