#include <stdio.h>
#include <stdlib.h>
#include "data.h"

Data *data_construct(char *word, char *file, char *qnt)
{
    Data *d = (Data *)calloc(1, sizeof(Data));
    d->word = word;
    d->file = file;
    d->qnt = qnt;

    return d;
};


void data_destroy(Data *d)
{
    free(d);
}; 