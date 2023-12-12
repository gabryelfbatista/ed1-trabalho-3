#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"

typedef struct Item
{
    char *key;
    int qnt;
} Item;

Item *item_construct(char *key, int qnt)
{
    Item *i = (Item *)calloc(1, sizeof(Item));
    i->key = key;
    i->qnt = qnt;

    return i;
}

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

int main() {
    char c;
    char texto[200];
    int count = 0;
    char dir_name[30];

    Vector *words = vector_construct();

    scanf("%s", dir_name);
    strcat(dir_name, "/files.txt");
    printf("%s\n",dir_name);
    FILE *arq = fopen(dir_name, "r");
    if (arq == NULL)
    {
        printf("Nao tem arquivo\n");
    }
    
    for (c = getc(arq); c!= EOF; c = getc(arq))
    {
        if (c == '\n')
        {
            count++;
        }
    }
    printf("qtd linhas: %d\n", count);
    fclose(arq);

    FILE *arq2 = fopen("./small/files/a1.txt", "r");
    if (arq2 == NULL)
    {
        printf("Nao tem arquivo\n");
    }
    count = 0;
    for (c = getc(arq2); c!= EOF; c = getc(arq2))
    {
        if (c == '\n')
        {
            count++;
        }
    }

    fclose(arq2);

    FILE *arq3 = fopen("./small/files/a1.txt", "r");
    printf("qtd linhas: %d\n", count);

    for (int i = 0; i < count; i++)
    {
        fgets(texto, 199, arq3);

        words = string_split(words, texto);
    }
    for (int j = 0; j < vector_size(words); j++)
    {
        char *palavra = vector_get(words, j);
        printf("%s\n", palavra);
    }

    Vector *unique = vector_unique(words, compara_strings);
    HashTable *h = hash_table_construct(vector_size(unique), hash_indice, compara_strings);

    for (int j = 0; j < vector_size(unique); j++)
    {
        Item *i = item_construct(vector_get(unique, j), 1);
        hash_table_set(h, i->key, i);
    }

    Item *aux = hash_table_get(h, "agua");

    // printf("Nome: %s\n", aux->key);
    // printf("Quantidade: %d\n", aux->qnt);

    // aux = hash_table_get(h, "azul");
    // printf("Nome: %s\n", aux->key);
    // printf("Quantidade: %d\n", aux->qnt);

    aux = hash_table_pop(h, "agua");
    printf("Nome: %s\n", aux->key);
    printf("Quantidade: %d\n", aux->qnt);

    aux = hash_table_pop(h, "azul");
    printf("Nome: %s\n", aux->key);
    printf("Quantidade: %d\n", aux->qnt);
 
    // int idx = hash_indice("1231542", 5);
    // printf("%d\n", idx);
    return 0;
}