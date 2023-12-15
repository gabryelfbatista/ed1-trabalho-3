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


int compara_strings(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

void key_destroy(void *k)
{
    free(k);
}