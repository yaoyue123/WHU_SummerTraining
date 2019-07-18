#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} Point;

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
    int **vis = malloc(sizeof(int *) * state.n);

    for(int i = 0; i < state.n; i++) {
        vis[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            vis[i][j] = 0;
        }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType E;

    E.x = start_x;
    E.y = start_y;
    E.step = -1;
    E.before = -1;
    vis[E.x][E.y] = 1;
    enQueue(q, E);
    char *path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        path[i] = 0;
    while(!QueueEmpty(q)) {
        ElemType temp;
        deQueue(q, &temp);
        for(int i = 0; i < 4; i++) {
            ElemType E;

            E.x = temp.x + dirx[i];
            E.y = temp.y + diry[i];
            E.step = temp.step + 1;
            E.dir = dir[i];
            E.before = q->front;

            if(E.x >= 0 && E.x < state.n
            && E.y >= 0 && E.y < state.m
            && vis[E.x][E.y] == 0 && state.grid[E.x][E.y] == 0) {
                vis[E.x][E.y] = 1;
                enQueue(q, E);
                if(E.x == end_x && E.y == end_y) {
                    int i = q->rear;
                    (*dist) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < state.n; i++) {
                        free(vis[i]);
                    }
                    free(vis);
                    DestroyQueue(q);
                    return path;
                }
            }
        }
    }

    free(path);
    for(int i = 0; i < state.n; i++) {
        free(vis[i]);
    }
    free(vis);
    DestroyQueue(q);
    return NULL;
}

void enumerate(game_state_t state, Point *goal, 
int beanNum, int *s, int t, int **distList, int *startList, \
        int *bestseq, int *mindist, int *vis) 
{
    if(t == beanNum) {
        int distsum = 0;
        if(startList[s[0]] != -1) {
            distsum += startList[s[0]];
        }
        else 
        {
            int dist;

            char *path = bfs(state, state.start_x, state.start_y, 
            goal[s[0]].x, goal[s[0]].y, &dist);
            free(path);
            distsum += dist;
            startList[s[0]] = dist;
        }

        for(int i = 1; i < beanNum; i++) {
            if(distList[s[i - 1]][s[i]] != -1) {
                distsum += distList[s[i - 1]][s[i]];
            }
            else {
                int dist;
                char *path = bfs(state, goal[s[i - 1]].x, goal[s[i - 1]].y,
                 goal[s[i]].x, goal[s[i]].y, &dist);
                free(path);
                distsum += dist;
                distList[s[i - 1]][s[i]] = distList[s[i]][s[i - 1]] = dist;
            }
        }

        if(distsum < (*mindist)) {
            (*mindist) = distsum;
            memcpy(bestseq, s, sizeof(int) * beanNum);
        }
        return;
    }
    for(int i = 0; i < beanNum; i++) {
        if(vis[i] == 0) {
            s[t] = i;
            vis[i] = 1;
            enumerate(state, goal, beanNum, s, t + 1, distList, startList, bestseq, mindist, vis);
            vis[i] = 0;
        }
    }
}


int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    srand(time(NULL));
    Point *goal;//用来记录豆子位置的数组
    int beanNum = 0;//用来记录豆子个数的数组
    int **location = malloc(sizeof(int *) * state.n);//用于记录食物在数组中的位置
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    goal = (Point *)malloc(sizeof(Point) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {//如果这个地方有食物，就把这个食物位置加入数组
                goal[beanNum].x = i;
                goal[beanNum].y = j;
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

    int *s = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录吃豆子的顺序
    int *bestseq = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录最佳吃豆子顺序
    int *vis = (int *)malloc(sizeof(int) * beanNum);//枚举函数有用
    for(int i = 0; i < beanNum; i++) {
        vis[i] = 0;
    }
    int mindist = 1073741824;

    enumerate(state, goal, beanNum, s, 0, distList, startList, bestseq, &mindist, vis);
    //
    int dist;
    char *path = bfs(state, state.start_x, state.start_y, goal[bestseq[0]].x, goal[bestseq[0]].y, &dist);
    printf("%s", path);
    free(path);

    for(int i = 1; i < beanNum; i++) {
        path = bfs(state, goal[bestseq[i - 1]].x, goal[bestseq[i - 1]].y, goal[bestseq[i]].x, goal[bestseq[i]].y, &dist);
        printf("%s", path);
        free(path);
    }

    free(goal);
    free(s);
    free(bestseq);
    free(vis);
    for(int i = 0; i < state.n; i++) {
        free(location[i]);
    }
    free(location);
    for(int i = 0; i < beanNum; i++) {
        free(distList[i]);
    }
    free(distList);
    free(startList);
  // 
  destroy(&state);
  return 0;
}
