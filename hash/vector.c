#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

struct Vector
{
    data_type *data;
    int size;
    int allocated;
};


static const int VECTOR_INIT_SIZE = 100;
static const int VECTOR_GROWTH_RATE = 2;

Vector *vector_construct()
{
    Vector *v = (Vector *)malloc(sizeof(Vector));
    v->allocated = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = (data_type *)calloc(VECTOR_INIT_SIZE, sizeof(data_type));
    return v;
};

void vector_destroy(Vector *v)
{
    free(v->data);
    free(v);
};

void vector_push_back(Vector *v, data_type val)
{
    if (v->size >= v->allocated)
    {
        v->allocated *= VECTOR_GROWTH_RATE;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    };

    v->data[v->size] = val;
    v->size++;
};

int vector_size(Vector *v)
{
    return v->size;
};

data_type vector_get(Vector *v, int i)
{
    if (v->allocated >= i && i >= 0)
    {
        return v->data[i];
    }
    else
    {
        printf("O indice nao e valido");
        exit(0);
    };
};

void vector_set(Vector *v, int i, data_type val)
{
    if (v->allocated >= i && i >= 0)
    {
        v->data[i] = val;
    }
    else
    {
        printf("O indice nao e valido");
    };
};

int vector_find(Vector *v, data_type val, int (*cmp)(data_type, data_type))
{
    int i = 0;
    while (i < vector_size(v))
    {
        if (!cmp(vector_get(v, i), val))
            return i;
        i++;
    }

    return -1;
}

data_type vector_remove(Vector *v, int i)
{
    data_type elementoRemovido = v->data[i];
    for (int j = i; j < v->size; j++)
    {
        v->data[j] = v->data[j + 1];
    };
    v->size--;
    return elementoRemovido;
};

data_type vector_pop_front(Vector *v)
{
    return vector_remove(v, 0);
};

data_type vector_pop_back(Vector *v)
{
    return vector_remove(v, v->size - 1);
};

void vector_insert(Vector *v, int i, data_type val)
{
    if (i <= v->size)
    {
        v->size++;
        for (int j = v->size; j >= i; j--)
        {
            if (j + 1 == v->allocated)
            {
                v->allocated *= VECTOR_GROWTH_RATE;
                v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
            }
            v->data[j + 1] = v->data[j];
        }
    }

    v->data[i] = val;
};

void vector_swap(Vector *v, int i, int j)
{
    data_type dataSalvo = v->data[i];

    v->data[i] = v->data[j];
    v->data[j] = dataSalvo;
};

void vector_sort(Vector *v)
{
    for (int i = 0; i < v->size; i++)
    {
        for (int j = 0; j < v->size; j++)
        {
            // printf("J +1 eh %d", j + 1);
            if (v->data[j] > v->data[j + 1] && j + 1 < v->size)
            {
                vector_swap(v, j, j + 1);
            }
        }
    }
};

int vector_binary_search(Vector *v, data_type val) {
    int idxMenor = 0;
    int idxMaior = v->size-1;
    int idxMeio;

    while(idxMenor <= idxMaior) {
        idxMeio = (idxMaior + idxMenor)/2;
        // printf("IdxMeio eh: %d\n", idxMeio );
        if (v->data[idxMeio] == val) {
            return idxMeio;
        } else if (val < v->data[idxMeio]) {
            idxMaior = idxMeio -1;
        } else if (val > v->data[idxMeio]) {
            // printf("O valor eh maior que o meio, indice do meio eh: %d\n", idxMeio);
            idxMenor = idxMeio + 1;
        }
    }
    
    return -1;
};

void vector_bubble_sort(Vector *v) {
    for (int i = 0; i < v->size - 1; i++) {
        int n_trocas = 0;
    
        for (int j = 0; j < v->size -1; j++) {
            if (v->data[j] > v->data[j+1]) {
                vector_swap(v, j, j+1);
                n_trocas++;
            }
        }

        if(n_trocas == 0){
            break;
        }
    }
};

Vector *vector_unique(Vector *v, int (*cmp)(data_type, data_type))
{
    Vector *output = vector_construct();

    for (int i = 0; i < vector_size(v); i++)
        if (vector_find(output, vector_get(v, i), cmp) == -1)
            vector_push_back(output, v->data[i]);

    return output;
}

void vector_reverse(Vector *v) {
    int j = v->size - 1;
    for (int i = 0; i < v->size; i++) {     
        if (j <= i) {
            break;
        } else {
            vector_swap(v, i, j);
            j--;
        }
    }
};
