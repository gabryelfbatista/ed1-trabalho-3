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

    HashTable *h = indexador_construct(dir_name, hash_indice, compara_strings);

    buscador_print(path, h, compara_strings);
    return 0;
}