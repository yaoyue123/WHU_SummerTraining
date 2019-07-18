#ifndef QUEUE_H_
#define QUEUE_H_


typedef struct {
    int x;
    int y;
    int step;
    char dir;
    int before;
} ElemType;

typedef struct 
{    
    ElemType *data;
    int MaxSize;
    int front,rear;                        
} SqQueue;

SqQueue *InitQueue(int MaxSize);       
void DestroyQueue(SqQueue *q);            
int QueueEmpty(SqQueue *q);               
int enQueue(SqQueue *q,ElemType e);       
int deQueue(SqQueue *q,ElemType *e);    

#endif