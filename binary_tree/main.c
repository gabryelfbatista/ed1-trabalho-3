#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

typedef struct Item
{
    int anos;
    int valor;
} Item;

Item *item_construct(int anos, int valor)
{
    Item *i = (Item *)calloc(1, sizeof(Item));
    i->anos = anos;
    i->valor = valor;

    return i;
}

int main()
{

    BinaryTree *arvore = binary_tree_construct();

    Item *um = item_construct(5, 5);

    Item *dois = item_construct(3, 3);
    Item *tres = item_construct(7, 7);
    Item *quatro = item_construct(1, 1);

    binary_tree_set(arvore, um->valor, um);
    binary_tree_set(arvore, dois->valor, dois);
    binary_tree_set(arvore, tres->valor, tres);
    binary_tree_set(arvore, quatro->valor, quatro);

    Item *aux = binary_tree_get(arvore, 7);

    printf("Valor do item: %d\n", aux->anos);

    return 0;
}