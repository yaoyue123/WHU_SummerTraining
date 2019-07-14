#include <stdio.h>

typedef struct node {
    int x, y, step;
} node;

typedef struct queue {
    node data[10100];
    int front, rear;
} queue;

void init(queue *q);
int size(queue *q);
void push(queue *q, node val);
node pop(queue *q);
