#ifndef _PAIR_H_
#define _PAIR_H_

#include "hash.h"

typedef struct Pair
{
    char *file;
    int qnt;
} Pair;

Pair *pair_construct(char *file, int qnt);

void pair_destroy(Pair *p);

#endif