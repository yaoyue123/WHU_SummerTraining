#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"
//以下代码部分改编自《数据结构教程（第五版）》（李春葆 主编）

CQueue *InitCQueue(int MaxSize)
{
    CQueue *q = (CQueue *)malloc(sizeof(CQueue));
    q->data = (CQueueType *)malloc(sizeof(CQueueType) * (MaxSize));
    q->MaxSize = MaxSize;
    q->front = q->rear = 0;
    return q;
}

void DestroyCQueue(CQueue *q)
{
    free(q->data);
    free(q);
}

int CQueueEmpty(CQueue *q)
{
    if(q->front == q->rear)
        return 1;
    return 0;
}

void enCQueue(CQueue *q, CQueueType e)
{
    if((q->rear + 1) % q->MaxSize == q->front)  //队满上溢出
        return;
    q->rear = (q->rear + 1) % q->MaxSize;
    q->data[q->rear] = e;
}

void deCQueue(CQueue *q, CQueueType *e)
{
    if(q->front == q->rear)     //队空下溢出
        return;
    q->front = (q->front + 1) % q->MaxSize;
    (*e) = q->data[q->front];
}
