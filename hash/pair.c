#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pair.h"
#include "utils.h"

Pair *pair_construct(char *file, int qnt)
{
    Pair *p = malloc(sizeof(Pair));
    p->file = strdup(file);
    p->qnt = qnt;

    return p;
}

void pair_destroy(Pair *p)
{
    free(p->file);
    free(p);
}
