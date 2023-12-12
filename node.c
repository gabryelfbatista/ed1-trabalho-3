
#include <stdlib.h>
#include "node.h"

Node *node_construct(data_type value, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));
    n->value = value;
    n->next = next;
    return n;
}

void node_destroy(Node *n)
{
    free(n);
}