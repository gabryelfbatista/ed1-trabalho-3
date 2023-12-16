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

    Vector *save_words = vector_construct();
    Vector *save_files = vector_construct();
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

        int qnt = 1;
        for (int j = 0; j < vector_size(words); j++)
        {
            char *word = vector_get(words, j);
            char *copy_file = strdup(file);

            HashTable *hash_file = hash_table_get(h, word);
            printf("A PALAVRA EH: %s!!!\n", word);

            if (hash_file == NULL)
            {   
                hash_file = hash_table_construct(10, hash_indice, compara_strings);
                char *copy_word = strdup(word);
                new_pair = pair_construct(copy_file, 1);
                hash_table_set(hash_file, new_pair->file, new_pair);
                hash_table_set(h, copy_word, hash_file);
                printf("NAO ENCONTREI ADICIONEI UM NOVO\n");

                // Data *aux = data_construct(word);
                // data_add_pair(aux, new_pair);
                // hash_table_set(h, aux->word, aux);

                // char *copy = strdup(aux->word);
                vector_push_back(save_words, copy_word);
                vector_push_back(save_files, copy_file);
            }
            else 
            {
                // Pair *aux_pair = data_get_pair(pair, file);
                Pair *aux  = hash_table_get(hash_file, file);
                
                if (aux == NULL)
                {
                    new_pair = pair_construct(file, 1);
                    hash_table_set(hash_file, new_pair->file, new_pair);

                    // new_pair = pair_construct(file, 1);
                    // data_add_pair(pair, new_pair);
                    vector_push_back(save_files, copy_file);
                    printf("Acrescentei mais um tipo de arquivo!\n");
                }
                else
                {
                    free(copy_file);
                    aux->qnt++;
                    printf("Somei mais um no arquivo %s quantidade: %d\n", file, aux->qnt);
                }
            }
        }
        
        libera_dados(words);
        vector_destroy(unique);

        // printf("NOME DO ARQUIVO ADICIONADO %s\n", new_pair->file);
        // int size = vector_size(save_files);
        // printf("Tamanho vetor de pares: %d", size);
    }

    Indexador *indexador = (Indexador *)calloc(1, sizeof(Indexador));
    indexador->hash = h;
    indexador->w = save_words;
    indexador->f = save_files;

    // for (int i = 0; i < vector_size(save_words); i++)
    // {
    //     Data *aux = vector_get(save_words, i);
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
    Vector *pairs  = vector_construct();
    Vector *unique_files = vector_unique(i->f, compara_strings);
    for (int j = 0; j < vector_size(i->w); j++)
    {
        char *palavra = vector_get(i->w, j);
        printf("a palavra na hora de destruir eh %s\n", palavra);
        HashTable *aux = hash_table_get(i->hash, vector_get(i->w, j));
        // hash_table_destroy(aux);
        for (int k = 0; k < vector_size(unique_files); k++)
        {
            Pair *aux_pair = hash_table_get(aux, vector_get(unique_files, k));
            if (aux_pair != NULL)
            {
                printf("Estou destruindo o arquivo %s da palavra %s\n", aux_pair->file, palavra);
                // pair_destroy(aux_pair);
                vector_push_back(pairs, aux_pair);
            }
        }
    }
    hash_table_destroy(i->hash);
    for (int i = 0; i < vector_size(pairs); i++)
    {
        pair_destroy(vector_get(pairs, i));
    }

    libera_dados(i->f);
    libera_dados(i->w);
    vector_destroy(unique_files);
    // hash_table_destroy(aux);
    

    free(i);
};