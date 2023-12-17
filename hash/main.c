#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "vector.h"
#include "indexador.h"
#include "utils.h"
#include "buscador.h"


double get_timestamp()
{
    struct timespec now;
    timespec_get(&now, TIME_UTC);
    return now.tv_sec + (((double)now.tv_nsec) / 1e9);
}

int main() 
{
    double start, end, dt;
    char search[200];
    char dir_name[100];
    char path[100];

    printf("Digite a pasta de arquivos: ");
    scanf("%s", dir_name);
    strcpy(path, dir_name);

    start = get_timestamp();
    Indexador *i = indexador_construct(dir_name);
    end = get_timestamp();
    dt = end - start;
    printf("O tempo para indexar foi: %f segundos\n\n", dt);

    printf("Digite as palavras de busca: ");
    fflush(stdin);
    scanf(" %[^\n]%*c", search);

    start = get_timestamp();
    buscador_print(search, path, i->hash);
    end = get_timestamp();
    dt = end - start;
    printf("O tempo para buscar foi: %f segundos\n", dt);

    indexador_destroy(i);
    return 0;
}