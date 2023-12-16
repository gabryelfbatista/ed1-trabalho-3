#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buscador.h"
#include "utils.h"
#include "data.h"
#include "vector.h"
#include "heap.h"

#define FILES_PATH "/files.txt"

typedef struct Relev
{
    char *name;
    int qnt;
} Relev;

Relev *relev_construct(char *name, int qnt)
{
    Relev *r = (Relev *)calloc(1, sizeof(Relev));
    r->name = malloc(sizeof(char)*100);
    strcpy(r->name, name);
    r->qnt = qnt;
    return r;
}

void relev_destroy(Relev *r)
{
    free(r->name);
    free(r);
}

void print_and_destroy(Heap *h)
{
    int count = 0;
    printf("Arquivos mais relevantes para busca selecionada:\n");
    while (!heap_empty(h))
    {
        Relev *aux = heap_pop(h);

        if(count < 10)
        {
            printf("%s  %d\n", aux->name, aux->qnt);
            count++;
        }
        relev_destroy(aux);
    }
    heap_destroy(h);
}

void buscador_print(char *dir_name, HashTable *h)
{
    char text[10000];
    char search[200];
    fflush(stdin);
    scanf(" %[^\n]%*c", search);

    Heap *heap = heap_construct();
    Vector *words = vector_construct();
    words = string_split(words, search);

    Vector *unique = vector_unique(words, compara_strings);

    strcat(dir_name, FILES_PATH);

    FILE *arq = fopen(dir_name, "r");   
    while (!feof(arq))
    {
        fgets(text, 9999, arq);
        char *content = strtok(text, "/");
        content = strtok(NULL, "\n");
        
        int total = 0;
        for (int i = 0; i < vector_size(unique); i++)
        {
            // char *palavra = vector_get(unique, i);
            // printf("Palavra: %s\n key: %d\n", palavra, hash_indice(h, palavra));

            Data *data_print = hash_table_get(h, vector_get(unique, i));
            if (data_print != NULL)
            {
                Pair *p = hash_table_get(data_print->pairs, content);
                if (p!= NULL)
                {
                    // printf("File: %s Quantidade: %d\n", p->file, p->qnt);
                    total = total + p->qnt;
                }
            }
        }
        // printf("Total de vezes do arquivo %s %d\n", content, total);
        if (total != 0)
        {
            // printf("%s\n", content);
            Relev *file_relev = relev_construct(content, total);
            heap_push(heap, file_relev, file_relev->qnt);
        }

    }
    print_and_destroy(heap);
    libera_dados(words);
    vector_destroy(unique);
    fclose(arq);

};