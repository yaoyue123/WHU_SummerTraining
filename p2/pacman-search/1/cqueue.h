//顺序队列（环形队列）基本运算算法
#ifndef CQUEUE_H_
#define CQUEUE_H_

typedef struct {
    int data;
    double distance;
} CQueueType;

typedef struct
{
    CQueueType *data;
    int MaxSize;
    int front,rear;		//队首和队尾指针
} CQueue;

CQueue *InitCQueue(int MaxSize);    //初始化环形队列
void DestroyCQueue(CQueue *q);   //销毁环形队列
int CQueueEmpty(CQueue *q);      //判断队列是否为空
void enCQueue(CQueue *q, CQueueType e);        //入队
void deCQueue(CQueue *q, CQueueType *e);        //出队

#endif
