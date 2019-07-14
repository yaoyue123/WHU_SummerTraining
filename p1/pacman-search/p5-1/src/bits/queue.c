#include "stdc++.h"

void queue_init(queue *q, int cap) {/*{{{*/
    q->data = (int*)malloc(sizeof(int) * cap);
    q->cap = cap;
    q->l = 0;
    q->r = -1;
}/*}}}*/

int queue_size(queue *q) {/*{{{*/
    return q->r - q->l + 1;
}/*}}}*/

void queue_expand(queue *q) {/*{{{*/
    q->cap *= 2;
    int *data = (int*)malloc(sizeof(int) * q->cap);
    for (int i = 0; i < q->r - q->l + 1; i++) {
        data[i] = q->data[i + q->l];
    }
    //free(q->data);
    q->data = data;
    q->r = q->r - q->l;
    q->l = 0;
}/*}}}*/

void queue_push(queue *q, int val) {/*{{{*/
    if (q->r >= q->cap) {
        queue_expand(q);
    }
    q->data[++q->r] = val;
}/*}}}*/

int queue_pop(queue *q) {/*{{{*/
    if (queue_size(q) <= 0) {
        printf("queue_pop\n");
        //exit(0);
    }
    return q->data[q->l++];
}/*}}}*/

