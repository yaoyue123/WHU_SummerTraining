#ifndef QUEUE_H_
#define QUEUE_H_

//顺序队列（非环形队列）基本运算算法
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
    int front,rear;                        //队头和队尾指针
} SqQueue;

SqQueue *InitQueue(int MaxSize);        //初始化队列，返回队列指针
void DestroyQueue(SqQueue *q);            //销毁队列
int QueueEmpty(SqQueue *q);                //判断队列是否为空
int enQueue(SqQueue *q,ElemType e);        //进队
int deQueue(SqQueue *q,ElemType *e);    //出队

#endif

