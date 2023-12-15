#ifndef _DATA_H_
#define _DATA_H_

#include "hash.h"


typedef struct Pair
{
    char *word;
    char *file;
    int qnt;
} Pair;

typedef struct Data
{
    char *word;
    HashTable *pairs;
} Data;

Pair *pair_construct(char *file, int qnt);

Pair *data_get_pair(Data *d, char* file);

Data *data_construct(char *word);

void data_add_pair(Data *d, char *file, int qnt);

void data_set_qnt(Data *d, int qnt);

void data_destroy(Data *d);

#endif