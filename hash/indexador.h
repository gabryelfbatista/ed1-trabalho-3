#ifndef _INDEXADOR_H_
#define _INDEXADOR_H_

#include "hash.h"

HashTable *indexador_construct(char *dir, HashFunction hash_fn, CmpFunction cmp_fn);

#endif