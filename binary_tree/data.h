#ifndef _DATA_H_
#define _DATA_H_

#include "binary_tree.h"


typedef struct Pair
{
    char *file;
    int qnt;
} Pair;

typedef struct Data
{
    char *word;
    BinaryTree *pairs;
} Data;

Pair *pair_construct(char *file, int qnt);

void pair_destroy(Pair *p);

Pair *data_get_pair(Data *d, char* file);

Data *data_construct(char *word);

void data_add_pair(Data *d, Pair *p);

void data_destroy(Data *d);

void data_pair_destroy(Data *d, char *file);

#endif