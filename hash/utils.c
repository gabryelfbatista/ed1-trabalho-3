#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"


Vector *string_split(Vector * v, char *str)
{
    Vector *words = v;

    // Split the string at every space character
    char *word = strtok(str, " ");

    while (word != NULL)
    {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }

    return words;
}


void libera_dados(Vector *words)
{
    for (int i = 0; i < vector_size(words); i++)
        // libera os espacos alocados pelo strdup
        free(vector_get(words, i));

    // libera o vetor
    vector_destroy(words);
}

int hash_indice(HashTable *h , void *p)
{
    char *palavra = (char *)p;
    int tam = strlen(palavra);
    int tam_tabela = hash_table_size(h);
    int soma = 0;
    int a = 31415;
    int b = 27183;


    for (int i = 0; i < tam; i++, a = (a*b) % (tam_tabela-1))
    {
        int ascii = palavra[i];
        soma = (soma * a + ascii) % tam_tabela ;
    }
    
    return soma;
}


int compara_strings(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}