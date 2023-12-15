#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"
#include "utils.h"
#include "indexador.h"
#include "buscador.h"

int main()
{

    char dir_name[100];
    char path[100];
    scanf("%s", dir_name);
    strcpy(path, dir_name);

    Indexador *i = indexador_construct(dir_name);

    buscador_print(path, i->b);

    // indexador_destroy(i);

    return 0;
}