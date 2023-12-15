#ifndef _UTILS_H_
#define _UTILS_H_

#include "vector.h"

Vector *string_split(Vector * v, char *str);

void libera_dados(Vector *words);

int compara_strings(void *a, void *b);

void key_destroy(void *k);

#endif