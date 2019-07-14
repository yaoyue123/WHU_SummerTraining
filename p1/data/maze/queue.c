#include <stdio.h>
#include "queue.h"

void init(queue *q) {
    q->front = 1;
    q->rear = 0;
}

int size(queue *q) {
    return q->rear - q->front + 1;
}

void push(queue *q, node val) {
    if (q->rear >= 10000) {
        exit(0);
    }
    q->data[++q->rear] = val;
}

node pop(queue *q) {
    if (size(q) <= 0) {
        exit(0);
    }
    return q->data[q->front++];
}

