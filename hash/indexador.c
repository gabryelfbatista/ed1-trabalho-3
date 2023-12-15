#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "hash.h"
#include "data.h"
#include "utils.h"

#define FILE_LIST_FILE_NAME "/files.txt"

HashTable *indexador_construct(char *dir, HashFunction hash_fn, CmpFunction cmp_fn)
{
    char *dir_name = dir;
    char path[100];
    char text[3000];
    strcpy(path, dir_name);
    strcat(path, "/");
    strcat(dir_name, FILE_LIST_FILE_NAME);

    HashTable *h = hash_table_construct(10, hash_fn, cmp_fn);

    FILE *arq = fopen(dir_name, "r");
    FILE *arq2;

    if (arq == NULL)
    {
        printf("Nao tem arquivo\n");
        return 0;
    }

    while (!feof(arq))
    {
        fgets(text, 2999, arq);
        char *content = strtok(text, "\n");
        // printf("%s\n", file_name);

        char aux_file[100];
        strcpy(aux_file, path);
        strcat(aux_file, content);

        char copy_file_name[100];
        strcpy(copy_file_name, content);
        char *file = strtok(copy_file_name, "/");
        file = strtok(NULL, "\n");

        arq2 = fopen(aux_file, "r");
        content = fgets(text, 2999, arq2);
        // printf("%s\n", content);
        fclose(arq2);

        Vector *words = vector_construct();

        words = string_split(words, content);
        Vector *unique = vector_unique(words, cmp_fn);

        for (int j = 0; j < vector_size(words); j++)
        {
            char *word = vector_get(words, j);
            
            Data *data = hash_table_get(h, word);
            // printf("A PALAVRA EH: %s!!!\n", word);

            if (data == NULL)
            {   
                // printf("NAO ENCONTREI ADICIONEI UM NOVO\n");
                Data *aux = data_construct(strdup(word));
                data_add_pair(aux, file, 1);
                // char *copy = strdup(aux->word);
                hash_table_set(h, aux->word, aux);
                // vector_push_back(datas, aux);
            }
            else 
            {
                Pair *aux_pair = data_get_pair(data, file);

                if (aux_pair == NULL)
                {
                    data_add_pair(data, file, 1);
                    // printf("Acrescentei mais um tipo de arquivo!\n");
                }
                else
                {
                    aux_pair->qnt++;
                    // printf("Somei mais um no arquivo %s\n", aux_pair->file);
                }
            }
        }
        
        libera_dados(words);
        vector_destroy(unique);
    }

    fclose(arq);

    return h;
};