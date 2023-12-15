#ifndef _INDEXADOR_H_
#define _INDEXADOR_H_

#include "vector.h"

typedef struct Indexador
{
    BinaryTree* b;
    Vector *datas;
    Vector *pairs;
} Indexador;

Indexador *indexador_construct(char *dir);

void indexador_destroy(Indexador*i);

#endif