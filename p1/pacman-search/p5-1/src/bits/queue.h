#ifndef queues
#define queues

//#include "stdc++.h"

typedef struct queue {/*{{{*/
    //int data[100];
    int *data;
    int l, r, cap;
} queue;/*}}}*/

void queue_init(queue *q, int cap);

int queue_size(queue *q);

void queue_expand(queue *q);

void queue_push(queue *q, int val);

int queue_pop(queue *q);

#endif
