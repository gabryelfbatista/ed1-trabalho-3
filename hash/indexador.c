#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "hash.h"
#include "pair.h"
#include "utils.h"
#include "indexador.h"

//Troque esses defines para ler o arquivo com os nomes de arquivos ou tamanho da hash
#define FILE_LIST_FILE_NAME "/files.txt"
#define HASH_SIZE 10

Indexador *indexador_construct(char *dir, HashFunction hash_fn, CmpFunction cmp_fn)
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

    Vector *save_words = vector_construct(); //para salvar as palavras que sao adicionadas na hash
    Vector *save_files = vector_construct(); //para salvar os nomes de arquivos que sao adicionados
    HashTable *h = hash_table_construct(HASH_SIZE, hash_fn, cmp_fn);

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
        Vector *unique = vector_unique(words, cmp_fn);
        
        Pair *new_pair;

        int qnt = 1;
        char *copy_word;
        char *copy_file;
        for (int j = 0; j < vector_size(words); j++)
        {
            char *word = vector_get(words, j);
            copy_file = strdup(file);
            
            //verifica se ja existe a palavra na hash
            HashTable *hash_file = hash_table_get(h, word);

            if (hash_file == NULL)
            {   
                // se nao existir, cria uma hash, um par arquivo quantidade e adiciona na hash da palavra
                HashTable *new_hash_file = hash_table_construct(10, hash_indice, compara_strings);
                copy_word = strdup(word);
                new_pair = pair_construct(copy_file, 1);

                hash_table_set(new_hash_file, copy_file, new_pair);
                hash_table_set(h, copy_word, new_hash_file);

                vector_push_back(save_words, copy_word);
                vector_push_back(save_files, copy_file);
            }
            else 
            {
                // se existir, busca o par do arquivo
                Pair *aux  = hash_table_get(hash_file, file);
                
                if (aux == NULL)
                {
                    //se ainda nao tiver um determinado arquivo pra palavra, cria o par e adiciona
                    new_pair = pair_construct(file, 1);
                    hash_table_set(hash_file, copy_file, new_pair);

                    vector_push_back(save_files, copy_file);
                }
                else
                {
                    // se existir apenas atualiza quantidade
                    free(copy_file);
                    aux->qnt++;
                }
            }
        }   
        libera_dados(words);
        vector_destroy(unique);
    }

    fclose(arq);
    

    Indexador *indexador = (Indexador *)calloc(1, sizeof(Indexador));
    indexador->hash = h;
    indexador->w = save_words;
    indexador->f = save_files;

    return indexador;
};


void indexador_destroy(Indexador *i)
{
    Vector *unique_files = vector_unique(i->f, compara_strings);

    for (int j = 0; j < vector_size(i->w); j++)
    {
        char *palavra = vector_get(i->w, j);
        printf("a palavra na hora de destruir eh %s\n", palavra);
        HashTable *aux = hash_table_get(i->hash, vector_get(i->w, j));

    
        for (int k = 0; k < vector_size(unique_files); k++)
        {
            char* removed_file = vector_get(unique_files, k);
            Pair *aux_pair = hash_table_get(aux, removed_file);
            if (aux_pair != NULL)
            {
                printf("Estou destruindo o arquivo %s da palavra %s\n", aux_pair->file, palavra);
                pair_destroy(aux_pair);
            }
        }
        // aqui a ideia era depois que remover todos itens da hash de uma palavra, destruir a hash relacionada a essa palavra
        // POREM A HASH_DESTROY nao quer funcionar
        // hash_table_destroy(aux);  
    }


    libera_dados(i->f);
    libera_dados(i->w);
    vector_destroy(unique_files);
    
    //mesma coisa aqui, a hash_destroy fica dando seg fault oq n faz sentido pq se eu consigo buscar todos itens...
    // hash_table_destroy(i->hash);

    free(i);
};