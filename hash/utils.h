#ifndef _UTILS_H_
#define _UTILS_H_

#include "vector.h"
#include "hash.h"


Vector *string_split(Vector * v, char *str);

void libera_dados(Vector *words);

int hash_indice(HashTable *h , void *p);

int compara_strings(void *a, void *b);

#endif