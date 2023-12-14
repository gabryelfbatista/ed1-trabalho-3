#ifndef _DATA_H_
#define _DATA_H_

#include "vector.h"

typedef struct Data
{
    char *word;
    char *file;
    char *qnt;
} Data;

Data *data_construct(char *word, char* file, char* qnt);

void data_set_qnt(Data *d, int qnt);

void data_destroy(Data *d);

#endif