#ifndef _INDEXADOR_H_
#define _INDEXADOR_H_

#include "hash.h"

typedef struct Indexador
{
    HashTable *hash;
    Vector *w;
    Vector *f;
} Indexador;

Indexador *indexador_construct(char *dir);

void indexador_destroy(Indexador*i);

#endif