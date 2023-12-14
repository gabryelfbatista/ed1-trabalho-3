#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"
#include "data.h"


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
    char *content;
    char *file_name;
    char text[15000];
    char dir_name[100];

    Vector *datas = vector_construct();
    HashTable *h = hash_table_construct(21000, hash_indice, compara_strings);

    scanf("%s", dir_name);
    char path[50];
    strcpy(path, dir_name);
    strcat(path, "/");

    strcat(dir_name, "/files.txt");
    FILE *arq = fopen(dir_name, "r");
    FILE *arq2;

    if (arq == NULL)
    {
        printf("Nao tem arquivo\n");
        return 0;
    }
    

    while(!feof(arq))
    {
        file_name = fgets(text, 14999, arq);
        file_name = strtok(file_name, "\n");

        char aux[100];
        strcpy(aux, path);
        strcat(aux, file_name);

        char *file = strtok(file_name, "/");
        file = strtok(NULL, "\n");

        arq2 = fopen(aux, "r");
        content = fgets(text, 14999, arq2);
        fclose(arq2);
        // printf("%s\n", content);

        Vector *words = vector_construct();

        words = string_split(words, content);
        Vector *unique = vector_unique(words, compara_strings);

        for (int j = 0; j < vector_size(unique); j++)
        {
            int count = 0;
            for (int k = 0; k < vector_size(words); k++)
            {
                if (compara_strings(vector_get(words, k), vector_get(unique, j)) == 0)
                {
                    count++;
                }
            }
            char *word = vector_get(unique, j);
            // printf("Palavra: %s\n Vezes: %d\n", word, count);

            Data *data = hash_table_get(h, word);

            if (data == NULL)
            {
                Data *aux = data_construct(strdup(word));
                data_add_pair(aux, file, count);
                hash_table_set(h, strdup(aux->word), aux);
                vector_push_back(datas, aux);
            }
            else
            {
                data_add_pair(data, file, count);
                hash_table_set(h, strdup(data->word), data);
            }

            // printf("Palavra: %s\n Vezes: %d\n", aux->word, aux->qnt);

        }

        libera_dados(words);
        vector_destroy(unique);
    }

    for (int i = 0; i < vector_size(datas); i++)
    {
        Data *d_removed = vector_get(datas, i);
        data_destroy(d_removed);
    }

    hash_table_destroy(h);
    vector_destroy(datas);

    fclose(arq);

    // Vector *unique = vector_unique(words, compara_strings);
    // HashTable *h = hash_table_construct(vector_size(unique), hash_indice, compara_strings);

    // for (int j = 0; j < vector_size(unique); j++)
    // {
    //     Item *i = item_construct(vector_get(unique, j), 1);
    //     hash_table_set(h, i->key, i);
    // }

    // Item *aux = hash_table_get(h, "agua");

    // printf("Nome: %s\n", aux->key);
    // printf("Quantidade: %d\n", aux->qnt);

    // aux = hash_table_get(h, "azul");
    // printf("Nome: %s\n", aux->key);
    // printf("Quantidade: %d\n", aux->qnt);

    // aux = hash_table_pop(h, "agua");
    // printf("Nome: %s\n", aux->key);
    // printf("Quantidade: %d\n", aux->qnt);

    // aux = hash_table_pop(h, "azul");
    // printf("Nome: %s\n", aux->key);
    // printf("Quantidade: %d\n", aux->qnt);
 
    // int idx = hash_indice("1231542", 5);
    // printf("%d\n", idx);
    return 0;
}