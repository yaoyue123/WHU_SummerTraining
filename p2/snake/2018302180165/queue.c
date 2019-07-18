#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
//以下代码由《数据结构教程》（第五版）（李春葆 主编）中的源代码改编而来

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
    if (q->rear == q->MaxSize - 1)        //队满上溢出
        return 0;                       //返回假
    q->rear++;                            //队尾增1
    q->data[q->rear] = e;                //rear位置插入元素e
    return 1;                           //返回真
}

int deQueue(SqQueue *q,ElemType *e)
{
    if (q->front == q->rear)            //队空下溢出
        return 0;
    q->front++;
    (*e) = q->data[q->front];
    return 1;
}