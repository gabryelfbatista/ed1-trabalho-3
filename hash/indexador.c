#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "hash.h"
#include "data.h"
#include "utils.h"
#include "indexador.h"

//Troque esses defines para ler o arquivo com os nomes de arquivos ou tamanho da hash
#define FILE_LIST_FILE_NAME "/files.txt"
#define HASH_SIZE 15000

Indexador *indexador_construct(char *dir, HashFunction hash_fn, CmpFunction cmp_fn)
{
    char *dir_name = dir;
    char path[100];
    char text[10000];
    strcpy(path, dir_name);
    strcat(path, "/");
    strcat(dir_name, FILE_LIST_FILE_NAME);

    Vector *save_datas = vector_construct();
    Vector *save_pairs = vector_construct();
    HashTable *h = hash_table_construct(HASH_SIZE, hash_fn, cmp_fn);

    FILE *arq = fopen(dir_name, "r");
    FILE *arq2;

    if (arq == NULL)
    {
        printf("Nao tem arquivo\n");
        return 0;
    }

    while (!feof(arq))
    {
        fgets(text, 9999, arq);
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
        content = fgets(text, 9999, arq2);
        // printf("%s\n", content);
        fclose(arq2);

        Vector *words = vector_construct();

        words = string_split(words, content);
        Vector *unique = vector_unique(words, cmp_fn);
        
        Pair *new_pair;
        for (int j = 0; j < vector_size(words); j++)
        {
            
            char *word = vector_get(words, j);
            
            Data *data = hash_table_get(h, word);
            // printf("A PALAVRA EH: %s!!!\n", word);

            if (data == NULL)
            {   
                // printf("NAO ENCONTREI ADICIONEI UM NOVO\n");
                Data *aux = data_construct(word);
                new_pair = pair_construct(file, 1);
                data_add_pair(aux, new_pair);
                // char *copy = strdup(aux->word);
                hash_table_set(h, aux->word, aux);
                vector_push_back(save_datas, aux);
                vector_push_back(save_pairs, new_pair);
            }
            else 
            {
                Pair *aux_pair = data_get_pair(data, file);

                if (aux_pair == NULL)
                {
                    new_pair = pair_construct(file, 1);
                    data_add_pair(data, new_pair);
                    vector_push_back(save_pairs, new_pair);
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

        // printf("NOME DO ARQUIVO ADICIONADO %s\n", new_pair->file);
        // int size = vector_size(save_pairs);
        // printf("Tamanho vetor de pares: %d", size);
    }

    Indexador *indexador = (Indexador *)calloc(1, sizeof(Indexador));
    indexador->hash = h;
    indexador->datas = save_datas;
    indexador->pairs = save_pairs;

    // for (int i = 0; i < vector_size(save_datas); i++)
    // {
    //     Data *aux = vector_get(save_datas, i);
    //     Vector *unique_file_names = vector_unique(pair_file_name, compara_strings);
    //     for (int j = 0; j < vector_size(unique_file_names); j++)
    //     {
    //         char *file_name = vector_get(unique_file_names, j);
    //         printf("%s\n", file_name);
    //         data_pair_destroy(aux, file_name);
    //     }

    //     data_destroy(aux);
    // }

    fclose(arq);

    return indexador;
};

void indexador_destroy(Indexador *i)
{
    
    // for (int j = 0; j < vector_size(i->pairs); j++)
    // {
    //     pair_destroy(vector_get(i->pairs, j));
    // }

    // for (int j = 0; j < vector_size(i->datas); j++)
    // {
    //     data_destroy(vector_get(i->datas, j));
    // }

    hash_table_destroy(i->hash);
    free(i);
};