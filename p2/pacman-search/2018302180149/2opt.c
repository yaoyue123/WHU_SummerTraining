#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
typedef struct {
    int x;
    int y;
} Point;

char *bfs(game_state_t state, int start_x, int start_y, int end_x, int end_y, int *dist, int **location, int *bvisit) {
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

                        if(state.grid[q->data[i].x][q->data[i].y] == 1) {//如果路上有食物被吃 
                            bvisit[location[q->data[i].x][q->data[i].y]] = 1;//将这个食物置为已访问
                        }
                    
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


void greedy(game_state_t state, int **location, int *seq) {//通过贪心初始化吃豆子顺序
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
    elem.x = state.start_x;
    elem.y = state.start_y;
    elem.step = -1;
    elem.before = -1;
    visit[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    int ppoint = 0;
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
                if(state.food[elem.x][elem.y] == 1) {
                    seq[ppoint] = location[elem.x][elem.y];
                    ppoint++;
                    DestroyQueue(q);
                    q = InitQueue(state.m * state.n);
                    elem.step = -1;
                    elem.before = -1;
                    state.food[elem.x][elem.y] = 0;
                    enQueue(q, elem);
                    for(int i = 0; i < state.n; i++) {
                        for(int j = 0; j < state.m; j++) {
                            visit[i][j] = 0;
                        }
                    }
                    visit[elem.x][elem.y] = 1;
                    break;
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
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    srand(time(NULL));
    Point *bean;//用来记录豆子位置的数组
    int beanNum = 0;//用来记录豆子个数的数组
    int **location = malloc(sizeof(int *) * state.n);//用于记录食物在数组中的位置
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    bean = (Point *)malloc(sizeof(Point) * state.n * state.m);
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
    greedy(state, location, seq);//初始化吃豆子顺序
    int *visit = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录豆子是否已经被吃，要求每次之前必须全为0

    memset(visit, 0, sizeof(int) * beanNum);

    int dist;
    int distmin = 0;
    char *path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dist, location, visit);
    distmin += dist;
    free(path);
    startList[seq[0]] = dist;
    for(int i = 1; i < beanNum; i++) {
        int k = i;
        while(k < beanNum) {
            if(visit[seq[k]] == 1)//如果这个豆子已经被访问
                k++;
            else
                break;
        }
        if(k == beanNum)
            break;//说明豆子已经被吃光，跳出循环
        path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[k]].x, bean[seq[k]].y, &dist, location, visit);
        free(path);
        distmin += dist;
        distList[seq[i - 1]][seq[k]] = distList[seq[k]][seq[i - 1]] = dist;
    }

    //在下面用2-opt对路径进行调整
    for(register int i = 0; i < 1000000; i++) {
        int startPoint = rand() % beanNum;
        int endPoint = rand() % beanNum;
        if(startPoint >= endPoint) {
            i--;
            continue;
        }
        int *newseq = (int *)malloc(sizeof(int) * beanNum);
        //对原来序列进行翻转操作
        for(int i = 0; i < startPoint; i++) {
            newseq[i] = seq[i];
        }
        for(int i = startPoint; i <= endPoint; i++) {
            newseq[i] = seq[startPoint + endPoint - i];
        }
        for(int i = endPoint + 1; i < beanNum; i++) {
            newseq[i] = seq[i];
        }

        int dist;
        int distsum = 0;
        memset(visit, 0, sizeof(int) * beanNum);
        if(startList[newseq[0]] != -1) {
            distsum += startList[newseq[0]];
        } else {
            path = bfs(state, state.start_x, state.start_y, bean[newseq[0]].x, bean[newseq[0]].y, &dist, location, visit);
            free(path);
            distsum += dist;
            startList[newseq[0]] = dist;
        }
        for(int i = 1; i < beanNum; i++) {
            int k = i;
            while(k < beanNum) {
                if(visit[seq[k]] == 1)//如果这个豆子已经被访问
                    k++;
                else
                    break;
            }
            if(k == beanNum)
                break;//说明豆子已经被吃光，跳出循环

            if(distList[newseq[i - 1]][newseq[k]] != -1)
                distsum += distList[newseq[i - 1]][newseq[k]];
            else {
                path = bfs(state, bean[newseq[i - 1]].x, bean[newseq[i - 1]].y, bean[newseq[k]].x, bean[newseq[k]].y, &dist, location, visit);
                free(path);
                distsum += dist;
                distList[newseq[i - 1]][newseq[k]] = distList[newseq[k]][newseq[i - 1]] = dist;
            }
        }
        if(distsum < distmin) {
            distmin = distsum;
            memcpy(seq, newseq, sizeof(int) * beanNum);
        }
        free(newseq);
    }


    //
    memset(visit, 0, sizeof(int) * beanNum);
    path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dist, location, visit);
    printf("%s", path);
    free(path);

    for(int i = 1; i < beanNum; i++) {
        int k = i;
        while(k < beanNum) {
            if(visit[seq[k]] == 1)//如果这个豆子已经被访问
                k++;
            else
                break;
        }
        if(k == beanNum)
            break;//说明豆子已经被吃光，跳出循环

        path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[k]].x, bean[seq[k]].y, &dist, location, visit);
        printf("%s", path);
        free(path);
    }
    free(bean);
    free(seq);
    for(int i = 0; i < state.n; i++) {
        free(location[i]);
    }
    free(location);
    for(int i = 0; i < beanNum; i++) {
        free(distList[i]);
    }
    free(distList);
    free(startList);
    free(visit);
  // 
  destroy(&state);
  return 0;
}