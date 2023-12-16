#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "binary_tree.h"
#include "data.h"
#include "utils.h"
#include "indexador.h"

#define FILE_LIST_FILE_NAME "/files.txt"

Indexador *indexador_construct(char *dir)
{
    char *dir_name = dir;
    char path[100];
    char text[10000];

    strcpy(path, dir_name);
    strcat(path, "/");
    strcat(dir_name, FILE_LIST_FILE_NAME);

    FILE *arq = fopen(dir_name, "r");
    FILE *arq2;

    if (arq == NULL)
    {
        printf("A pasta buscada nao existe\n");
        exit(1);
    }

    Vector *save_datas = vector_construct(); //para salvar as palavras que sao adicionadas na hash
    Vector *save_pairs = vector_construct(); //para salvar os nomes de arquivos que sao adicionados
    BinaryTree *bt = binary_tree_construct(compara_strings, key_destroy, data_destroy);

    

    while (!feof(arq))
    {
        /**
         * Aqui foi a maracutaia que eu consegui fazer pra ler todos os arquivos
        */
        fgets(text, 9999, arq);
        char *content = strtok(text, "\n");

        char aux_file[100];
        strcpy(aux_file, path);
        strcat(aux_file, content);

        char copy_file_name[100];
        strcpy(copy_file_name, content);
        char *file = strtok(copy_file_name, "/");
        file = strtok(NULL, "\n");

        arq2 = fopen(aux_file, "r");
        content = fgets(text, 9999, arq2);
        fclose(arq2);

        Vector *words = vector_construct();

        words = string_split(words, content);
        Vector *unique = vector_unique(words, compara_strings);

        Pair *new_pair;
        for (int j = 0; j < vector_size(words); j++)
        {
            char *word = vector_get(words, j);
            
            Data *data = binary_tree_get(bt, word);

            if (data == NULL)
            {   
                Data *aux = data_construct(word);
                new_pair = pair_construct(file, 1);

                data_add_pair(aux, new_pair);
                binary_tree_set(bt, aux->word, aux);

                vector_push_back(save_datas, aux);
                vector_push_back(save_pairs, new_pair);
            }
            else 
            {
                Pair *aux_pair = binary_tree_get(data->pairs, file);

                if (aux_pair == NULL)
                {
                    new_pair = pair_construct(file, 1);
                    data_add_pair(data, new_pair);

                    vector_push_back(save_pairs, new_pair);
                }
                else
                {
                    aux_pair->qnt++;
                }
            }
        }
        libera_dados(words);
        vector_destroy(unique);
    }

    fclose(arq);

    Indexador *indexador = (Indexador *)calloc(1, sizeof(Indexador));
    indexador->b = bt;
    indexador->datas = save_datas;
    indexador->pairs = save_pairs;

    return indexador;
};

void indexador_destroy(Indexador *i)
{
    for (int j = 0; j < vector_size(i->pairs); j++)
    {
        pair_destroy(vector_get(i->pairs, j));
    }
    vector_destroy(i->pairs);

    for (int j = 0; j < vector_size(i->datas); j++)
    {
        data_destroy(vector_get(i->datas, j));
    }
    vector_destroy(i->datas);
    
    binary_tree_destroy(i->b);
    free(i);
};