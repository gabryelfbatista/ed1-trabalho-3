
#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_construct();
void heap_push(Heap *heap, void *data, double priority);
int heap_empty(Heap *heap);
void heap_destroy(Heap *heap);
void *heap_pop(Heap *heap);

#endif