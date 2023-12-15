#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"
#include "data.h"
#include "indexador.h"
#include "utils.h"
#include "buscador.h"


int main() {
    char dir_name[100];
    char path[100];
    scanf("%s", dir_name);
    strcpy(path, dir_name);

    Indexador *i = indexador_construct(dir_name, hash_indice, compara_strings);

    buscador_print(path, i->hash);

    // indexador_destroy(i);
    return 0;
}