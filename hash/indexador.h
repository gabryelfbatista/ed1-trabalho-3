#ifndef _INDEXADOR_H_
#define _INDEXADOR_H_

#include "hash.h"

typedef struct Indexador
{
    HashTable *hash;
    Vector *datas;
    Vector *pairs;
} Indexador;

Indexador *indexador_construct(char *dir, HashFunction hash_fn, CmpFunction cmp_fn);

void indexador_destroy(Indexador*i);

#endif