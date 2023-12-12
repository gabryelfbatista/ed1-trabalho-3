#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "node.h"

struct List
{
    Node *head;
    Node *last;
    int size;
};

List *list_construct()
{
    List *l = (List*)malloc(sizeof(List));
    l->head = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
};

void list_push_front(List *l, data_type data)
{
    Node *newNode = node_construct(data, NULL, NULL);

    if(l->head == NULL)
    {
        l->head = l->last = newNode;
    } else {
        newNode->next = l->head;
        l->head = l->head->prev = newNode;
    }

    l->size++;
};

int list_size(List *l)
{
    return l->size;
};

void list_print(List *l, void (*print_fn)(data_type))
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

void list_print_reverse(List *l, void (*print_fn)(data_type))
{
    Node *aux = l->last;
    printf("[");
    for (int i=0; i<l->size; i++){
        if (i == l->size-1) {
            print_fn(aux->value);
            aux = aux->prev;
        } else {
            print_fn(aux->value);
            printf(", ");
            aux = aux->prev;
        }
    }
    printf("]");
};

data_type list_get(List *l, int i)
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

data_type list_pop_front(List *l)
{
    if (l->head == NULL)
    {
        exit(printf("List is empty"));
    }

    Node *aux = l->head;
    data_type data = aux->value;

    l->head = aux->next;data_type list_pop_back(List *l);
    l->size--;

    if (l->size <= 1)
    {
        l->last = l->head;
    }

    return data;
};

void list_push_back(List *l, data_type data)
{
    Node *newNode = node_construct(data, NULL, NULL);

    if (l->head == NULL)
    {
        l->last = newNode;
        l->head = newNode;
    }
    else
    {
        newNode->prev = l->last;
        l->last->next = newNode;
        l->last = newNode;
    }

    l->size++;
    
};

data_type list_pop_back(List *l)
{
    if (l->head == NULL)
    {
        exit(printf("List is empty"));
    }

    Node *aux = l->last;
    data_type data = aux->value;

    l->last = l->last->prev;

    if (l->last != NULL)
    {
        l->last->next = NULL; 
    }
    

    node_destroy(aux);
    l->size--;

    if (l->size <= 1)
    {
        l->last = l->head;
    }

    return data;
};

ListIterator *list_front_iterator(List *l)
{
    ListIterator *it = (ListIterator *)calloc(1, sizeof(ListIterator));
    it->current = l->head;
    return it;
};

ListIterator *list_back_iterator(List *l)
{
    ListIterator *it = (ListIterator *)calloc(1, sizeof(ListIterator));
    it->current = l->last;
    return it;
};

data_type *list_iterator_next(ListIterator *it)
{
    data_type *val = &(it->current->value);
    it->current = it->current->next;
    return val;
};

data_type *list_iterator_previous(ListIterator *it)
{
    data_type *val = &(it->current->value);
    it->current = it->current->prev;
    return val;
};

bool list_iterator_is_over(ListIterator *it)
{
    return (it->current == NULL);
};

void list_iterator_destroy(ListIterator *it)
{
    free(it);
};

void list_destroy(List *l)
{
    free(l);
};