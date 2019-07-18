#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


SqQueue *InitQueue(int MaxSize)
{
    SqQueue *q = (SqQueue *)malloc (sizeof(SqQueue));
    q->data = (ElemType *)malloc (sizeof(ElemType) * MaxSize);
    q->MaxSize = MaxSize;
    q->front = q->rear = -1;
    return q;
}

void DestroyQueue(SqQueue *q)
{
    free(q->data);
    free(q);
}

int QueueEmpty(SqQueue *q)
{
    if(q->front == q->rear)
        return 1;
    else
        return 0;
}

int enQueue(SqQueue *q,ElemType e)
{
    if (q->rear == q->MaxSize - 1)        
        return 0;                      
    q->rear++;                            
    q->data[q->rear] = e;               
    return 1;                         
}

int deQueue(SqQueue *q,ElemType *e)
{
    if (q->front == q->rear)            
        return 0;
    q->front++;
    (*e) = q->data[q->front];
    return 1;
}