
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

const int HEAP_INITIAL_CAPACITY = 10;
const int HEAP_GROW_RATE = 2;

typedef struct
{
    void *data;
    double priority;
} HeapNode;

struct Heap
{
    HeapNode *nodes;
    int size;
    int capacity;
};

Heap *heap_construct()
{
    Heap *heap = malloc(sizeof(Heap));

    heap->nodes = malloc(sizeof(HeapNode) * HEAP_INITIAL_CAPACITY);
    heap->size = 0;
    heap->capacity = 10;

    return heap;
}

void _swap_nodes(Heap *heap, int i, int j)
{
    HeapNode temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = temp;
}

void _heapify_up(Heap *heap, int idx)
{
    int parent = (idx - 1) / 2;

    if ((parent >= 0) && (heap->nodes[parent].priority < heap->nodes[idx].priority))
    {
        _swap_nodes(heap, idx, parent);
        _heapify_up(heap, parent);
    }
}

void _heapify_down(Heap *heap, int idx)
{
    int idx_maior, idx_left, idx_right;

    while (idx < heap->size)
    {
        idx_left = idx*2 + 1;
        idx_right = idx*2 + 2;
        if (idx_right < heap->size && heap->nodes[idx_right].priority >= heap->nodes[idx_left].priority)
        {
            idx_maior = idx_right;

            if (heap->nodes[idx].priority < heap->nodes[idx_maior].priority)
            {
                _swap_nodes(heap, idx, idx_maior);
            }
            idx = idx_maior;

        }        
        else if (idx_left < heap->size && heap->nodes[idx_left].priority >= heap->nodes[idx_right].priority)
        {
            idx_maior = idx_left;

            if (heap->nodes[idx].priority < heap->nodes[idx_maior].priority)
            {
                _swap_nodes(heap, idx, idx_maior);
            }
            idx = idx_maior;

        }
        else break;
    }
}

void heap_push(Heap *heap, void *data, double priority)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= HEAP_GROW_RATE;
        heap->nodes = realloc(heap->nodes, sizeof(HeapNode) * heap->capacity);
    }

    // add the node in the end of the array (last leaf of the binary tree representation)
    heap->nodes[heap->size].data = data;
    heap->nodes[heap->size].priority = priority;
    heap->size++;

    // enforce the heap property
    _heapify_up(heap, heap->size - 1);
}

int heap_empty(Heap *heap)
{
    return (heap->size == 0);
}

void heap_destroy(Heap *heap)
{
    free(heap->nodes);
    free(heap);
}

void *heap_pop(Heap *heap)
{
    if (heap_empty(heap))
        exit(printf("Error:: heap_pop:: heap is empty\n"));

    // *************************************
    // TODO!
    // *************************************

    HeapNode no_removido = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size-1];
    heap->size--;

    _heapify_down(heap, 0);
    return no_removido.data;
}