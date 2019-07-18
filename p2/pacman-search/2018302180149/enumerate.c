#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

char *bfs(game_state_t state, int start_x, int start_y, int end_x, int end_y, int *dist) {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **visit = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        visit[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            visit[i][j] = 0;
        }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = start_x;
    elem.y = start_y;
    elem.step = -1;
    elem.before = -1;
    visit[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType elem;
            elem.x = temp.x + dirx[i];
            elem.y = temp.y + diry[i];
            elem.step = temp.step + 1;
            elem.dir = dir[i];
            elem.before = q->front;
            if(elem.x >= 0 && elem.x < state.n
            && elem.y >= 0 && elem.y < state.m
            && visit[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(elem.x == end_x && elem.y == end_y) {
                    int i = q->rear;
                    (*dist) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < state.n; i++) {
                        free(visit[i]);
                    }
                    free(visit);
                    DestroyQueue(q);
                    return path;
                }
            }
        }
    }

    free(path);
    for(int i = 0; i < state.n; i++) {
        free(visit[i]);
    }
    free(visit);
    DestroyQueue(q);
    return NULL;
}

void enumerate(game_state_t state, ElemType *bean, int beanNum, int *seq, int t, int **distList, int *startList, \
        int *bestseq, int *mindist, int *visit) 
{
    if(t == beanNum) {
        int distsum = 0;
        if(startList[seq[0]] != -1) {
            distsum += startList[seq[0]];
        }
        else {
            int dist;
            char *path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dist);
            free(path);
            distsum += dist;
            startList[seq[0]] = dist;
        }

        for(int i = 1; i < beanNum; i++) {
            if(distList[seq[i - 1]][seq[i]] != -1) {
                distsum += distList[seq[i - 1]][seq[i]];
            }
            else {
                int dist;
                char *path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[i]].x, bean[seq[i]].y, &dist);
                free(path);
                distsum += dist;
                distList[seq[i - 1]][seq[i]] = distList[seq[i]][seq[i - 1]] = dist;
            }
        }

        if(distsum < (*mindist)) {
            (*mindist) = distsum;
            memcpy(bestseq, seq, sizeof(int) * beanNum);
        }
        return;
    }
    for(int i = 0; i < beanNum; i++) {
        if(visit[i] == 0) {
            seq[t] = i;
            visit[i] = 1;
            enumerate(state, bean, beanNum, seq, t + 1, distList, startList, bestseq, mindist, visit);
            visit[i] = 0;
        }
    }
}


int main() {
  int count = 0;
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
    srand(time(NULL));
    ElemType *bean;//用来记录豆子位置的数组
    int beanNum = 0;//用来记录豆子个数的数组
    int **location = malloc(sizeof(int *) * state.n);//用于记录食物在数组中的位置
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    bean = (ElemType *)malloc(sizeof(ElemType) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {//如果这个地方有食物，就把这个食物位置加入数组
                bean[beanNum].x = i;
                bean[beanNum].y = j;
                location[i][j] = beanNum;//更新地址表
                beanNum++;
            }
        }
    }

    int *startList = malloc(sizeof(int) * beanNum);//用于存储起点到豆子的距离
    int **distList = malloc(sizeof(int *) * beanNum);//用于存储豆子之间的距离，避免重复计算
    for(int i = 0; i < beanNum; i++) {
        startList[i] = -1;
        distList[i] = malloc(sizeof(int) * beanNum);
        for(int j = 0; j < beanNum; j++) {
            distList[i][j] = -1;
        }
    }
    int *seq = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录吃豆子的顺序
    int *bestseq = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录最佳吃豆子顺序
    int *visit = (int *)malloc(sizeof(int) * beanNum);//枚举函数有用
    for(int i = 0; i < beanNum; i++) {
        visit[i] = 0;
    }
    int mindist = 1073741824;

    enumerate(state, bean, beanNum, seq, 0, distList, startList, bestseq, &mindist, visit);
    int dist;
    char *path = bfs(state, state.start_x, state.start_y, bean[bestseq[0]].x, bean[bestseq[0]].y, &dist);
    while(path[count]!='\0') {
      printf("%c",path[count]);
      count++;
    }
    free(path);

    for(int i = 1; i < beanNum; i++) {
        path = bfs(state, bean[bestseq[i - 1]].x, bean[bestseq[i - 1]].y, bean[bestseq[i]].x, bean[bestseq[i]].y, &dist);
        count = 0;
        while(path[count]!='\0') {
        printf("%c",path[count]);
        count++;
      }
        free(path);
    }
    free(bean);
    free(seq);
    free(bestseq);
    free(visit);
    for(int i = 0; i < state.n; i++) {
        free(location[i]);
    }
    free(location);
    for(int i = 0; i < beanNum; i++) {
        free(distList[i]);
    }
    free(distList);
    free(startList);
  destroy(&state);
  return 0;
}
