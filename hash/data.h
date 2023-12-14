#ifndef _DATA_H_
#define _DATA_H_

#include "vector.h"


typedef struct Data
{
    char *word;
    Vector *pairs;
} Data;

Data *data_construct(char *word);

void data_add_pair(Data *d, char *file, int qnt);

void data_set_qnt(Data *d, int qnt);

void data_destroy(Data *d);

#endif