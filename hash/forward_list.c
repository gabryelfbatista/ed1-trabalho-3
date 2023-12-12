#include "forward_list.h"
#include "node.h"
#include <stdlib.h>
#include <stdio.h>

struct ForwardList
{
    Node *head;
    int size;
};

ForwardList *forward_list_construct() 
{
    return calloc(1, sizeof(ForwardList));
};

void forward_list_push_front(ForwardList *l, data_type val) 
{ 
    l->head = node_construct(val, l->head);
    l->size++;
};

int forward_list_size(ForwardList *l)
{
    return l->size;
};

void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node *aux = l->head;
    printf("[");
    for (int i=0; i<l->size; i++){
        if (i == l->size-1) {
            print_fn(aux->value);
            aux = aux->next;
        } else {
            print_fn(aux->value);
            printf(", ");
            aux = aux->next;
        }
    }
    printf("]");
};

data_type forward_list_get(ForwardList *l, int i)
{
    if (i < 0 || i>=l->size) {
        exit(printf("Error: index out of bounds."));
    }

    Node *aux = l->head;
    for (int j=0; j<i; j++){
        aux = aux->next;
    }
    return aux->value;
};

data_type forward_list_pop_front(ForwardList *l)
{
    Node *aux = l->head;

    if (l->size ==0 ){
        exit(printf("Error: forwardlist has 0 nodes"));
    } else if (l->size == 1) {
        l->head = NULL;
    } else {
        l->head = aux->next;
    }

    l->size--;
    return aux->value;
    node_destroy(aux);
};

ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *l2 = forward_list_construct();
    
    Node *aux = l->head;
    while(aux != NULL)
    {
        forward_list_push_front(l2, aux->value);
        aux = aux->next;
    }
    l2->size = l->size;
    return l2;
};

void forward_list_remove(ForwardList *l, data_type val, int (*cmp)(data_type, data_type))
{
    Node *atual = l->head;
    Node *anterior = NULL;


    int qtd = 0;

    //primeiro passa pela lista contando quantos nós daquele valor tem
    while (atual != NULL)
    {
        if (cmp(val, atual->value) == 0)
        {
            qtd++;
        }  
        atual = atual->next;
    }

    //verifica se existe o valor q quer ser removido
    if (qtd == 0){
        exit(printf("Error: value dont exist in list"));
    }

    atual = l->head;

    //depois vai varrendo com dois vetores e apagando os nós com o valor pedido
    //até que a quantidade contada seja 0
    while (atual != NULL)
    {   
        if (val == atual->value) {
            if (anterior == NULL){
                 l->head = atual->next;
            }
            else 
            {
                anterior->next = atual->next;
            }
            node_destroy(atual);
            l->size--;
            qtd--;
            if (qtd == 0){
                break;
            } else {
                atual = l->head;
                anterior = NULL;
            }
        }

        anterior = atual;
        atual = atual->next;
    }
};

/*
Cria um ponteiro Node auxiliar pra iterar sobre a lista e adiciona cada
elemento da segunda lista na frente da primeira lista
*/ 
void forward_list_cat(ForwardList *l, ForwardList *m)
{
    Node *aux = m->head;

    while(aux != NULL)
    {
        forward_list_push_front(l, aux->value);
        aux = aux->next;
    }
};

void forward_list_destroy(ForwardList *l) 
{
    Node *aux = l->head;
    Node *new_next;
    while (aux != NULL)
    {
        new_next = aux->next;
        free(aux);
        aux = new_next;
    }
    free(l);
};