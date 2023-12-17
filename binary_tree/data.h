#ifndef _DATA_H_
#define _DATA_H_

#include "binary_tree.h"

// struct pra salvar nome do arquivo e quantidade
typedef struct Pair
{
    char *file;
    int qnt;
} Pair;

// struct com nome de uma palavra e uma arvore associada a ela
typedef struct Data
{
    char *word;
    BinaryTree *pairs;
} Data;

// aloca na memoria um Par arquivo-quantidade
Pair *pair_construct(char *file, int qnt);

// desaloca um Pair arquivo-quantidade
void pair_destroy(void *p);

// constroi o tipo Data a partir de uma palavra
Data *data_construct(char *word);

// adiciona um par arquivo-quantidade na arvore associada a palavra
void data_add_pair(Data *d, Pair *p);

// desaloca um struct tipo Data e sua arvore binaria
void data_destroy(void *d);

// desaloca um par de um arvore binaria do Data
void data_pair_destroy(Data *d, char *file);

#endif