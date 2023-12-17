#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buscador.h"
#include "utils.h"
#include "data.h"
#include "vector.h"
#include "binary_tree.h"
#include "heap.h"

#define FILES_PATH "/files.txt"


/**
 * Relev -> relevancia
 * struct criado para salvar o nome de um arquivo e quantas vezes as palavras
 * que foram buscadas apareceram nesse tal arquivo
*/
typedef struct Relev
{
    char *name;
    int qnt;
} Relev;


// aloca na memoria esse struct Relev
Relev *relev_construct(char *name, int qnt)
{
    Relev *r = (Relev *)calloc(1, sizeof(Relev));
    r->name = malloc(sizeof(char)*100);
    strcpy(r->name, name);
    r->qnt = qnt;
    return r;
}


// printa e desaloca tudo da heap de relevantes
void relev_destroy(Relev *r)
{
    free(r->name);
    free(r);
}


void print_and_destroy(Heap *h)
{
    int count = 0;
    printf("\nArquivos mais relevantes para busca selecionada:\n");
    while (!heap_empty(h))
    {
        Relev *aux = heap_pop(h);

        if(count < 10)
        {
            printf("%s   %d\n", aux->name, aux->qnt);
            count++;
        }
        relev_destroy(aux);
    }
    printf("\n");
    heap_destroy(h);
}

void buscador_print(char *search, char *dir_name, BinaryTree *b)
{
    char text[1000];

    Heap *heap = heap_construct();
    Vector *words = vector_construct();
    words = string_split(words, search);

    Vector *unique = vector_unique(words, compara_strings);

    strcat(dir_name, FILES_PATH);

    FILE *arq = fopen(dir_name, "r");   
    while (!feof(arq))
    {
        fgets(text, 999, arq);
        char *content = strtok(text, "/");
        content = strtok(NULL, "\n");
        
        int total = 0;

        // pra cada palavra buscada busca na arvore e soma quantas vezes apareceram a partir
        // do nome de um determinado arquivo
        for (int i = 0; i < vector_size(unique); i++)
        {

            Data *data_print = binary_tree_get(b, vector_get(unique, i));
            if (data_print != NULL)
            {
                Pair *p = binary_tree_get(data_print->pairs, content);
                if (p!= NULL)
                {
                    total = total + p->qnt;
                }
            }
        }

        if (total != 0)
        {
            Relev *file_relev = relev_construct(content, total);
            heap_push(heap, file_relev, file_relev->qnt);
        }

    }
    print_and_destroy(heap);
    libera_dados(words);
    vector_destroy(unique);
    fclose(arq);

};