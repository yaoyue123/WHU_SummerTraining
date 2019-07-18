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

char *bfs(game_state_t state, int start_x, int start_y, int end_x, int end_y, int *Dist, int **Lo, int *bvisit) {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **Vis = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        Vis[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            Vis[i][j] = 0;
        }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = start_x;
    elem.y = start_y;
    elem.step = -1;
    elem.before = -1;
    Vis[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *Path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        Path[i] = 0;
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
            && Vis[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                Vis[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(elem.x == end_x && elem.y == end_y) {
                    int i = q->rear;
                    (*Dist) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {

                        if(state.grid[q->data[i].x][q->data[i].y] == 1) {//如果路上有食物被吃 
                            bvisit[Lo[q->data[i].x][q->data[i].y]] = 1;//将这个食物置为已访问
                        }
                    
                        Path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < state.n; i++) {
                        free(Vis[i]);
                    }
                    free(Vis);
                    DestroyQueue(q);
                    return Path;
                }
            }
        }
    }

    free(Path);
    for(int i = 0; i < state.n; i++) {
        free(Vis[i]);
    }
    free(Vis);
    DestroyQueue(q);
    return NULL;
}


void greedy(game_state_t state, int **Lo, int *seq) {//通过贪心初始化吃豆子顺序
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int **Vis = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
      Vis[i] = malloc(sizeof(int) * state.m);
      for(int j = 0; j < state.m; j++) {
          Vis[i][j] = 0;
      }
    }
    SqQueue *q = InitQueue(state.n * state.m);
    ElemType elem;
    elem.x = state.start_x;
    elem.y = state.start_y;
    elem.step = -1;
    elem.before = -1;
    Vis[elem.x][elem.y] = 1;
    enQueue(q, elem);
    char *Path = (char *)malloc(sizeof(char) * state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        Path[i] = 0;
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
            && Vis[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                Vis[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(state.food[elem.x][elem.y] == 1) {
                    seq[ppoint] = Lo[elem.x][elem.y];
                    ppoint++;
                    DestroyQueue(q);
                    q = InitQueue(state.m * state.n);
                    elem.step = -1;
                    elem.before = -1;
                    state.food[elem.x][elem.y] = 0;
                    enQueue(q, elem);
                    for(int i = 0; i < state.n; i++) {
                        for(int j = 0; j < state.m; j++) {
                            Vis[i][j] = 0;
                        }
                    }
                    Vis[elem.x][elem.y] = 1;
                    break;
                }
            }
        }
    }

    free(Path);
    for(int i = 0; i < state.n; i++) {
        free(Vis[i]);
    }
    free(Vis);
    DestroyQueue(q);
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    srand(time(NULL));
    Point *goal;//用来记录豆子位置的数组
    int goalnum = 0;//用来记录豆子个数的数组
    int **Lo = malloc(sizeof(int *) * state.n);//用于记录食物在数组中的位置
    for(int i = 0; i < state.n; i++) {
        Lo[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            Lo[i][j] = -1;
        }
    }
    goal = (Point *)malloc(sizeof(Point) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {//如果这个地方有食物，就把这个食物位置加入数组
                goal[goalnum].x = i;
                goal[goalnum].y = j;
                Lo[i][j] = goalnum;//更新地址表
                goalnum++;
            }
        }
    }

    int *Lstart = malloc(sizeof(int) * goalnum);//用于存储起点到豆子的距离
    int **Ldist = malloc(sizeof(int *) * goalnum);//用于存储豆子之间的距离，避免重复计算
    for(int i = 0; i < goalnum; i++) {
        Lstart[i] = -1;
        Ldist[i] = malloc(sizeof(int) * goalnum);
        for(int j = 0; j < goalnum; j++) {
            Ldist[i][j] = -1;
        }
    }

    int *seq = (int *)malloc(sizeof(int) * (goalnum + 5));//用于记录吃豆子的顺序
    greedy(state, Lo, seq);//初始化吃豆子顺序
    int *Vis = (int *)malloc(sizeof(int) * (goalnum + 5));//用于记录豆子是否已经被吃，要求每次之前必须全为0

    memset(Vis, 0, sizeof(int) * goalnum);

    int Dist;
    int mindist = 0;
    char *Path = bfs(state, state.start_x, state.start_y, goal[seq[0]].x, goal[seq[0]].y, &Dist, Lo, Vis);
    mindist += Dist;
    free(Path);
    Lstart[seq[0]] = Dist;
    for(int i = 1; i < goalnum; i++) {
        int k = i;
        while(k < goalnum) {
            if(Vis[seq[k]] == 1)//如果这个豆子已经被访问
                k++;
            else
                break;
        }
        if(k == goalnum)
            break;//说明豆子已经被吃光，跳出循环
        Path = bfs(state, goal[seq[i - 1]].x, goal[seq[i - 1]].y, goal[seq[k]].x, goal[seq[k]].y, &Dist, Lo, Vis);
        free(Path);
        mindist += Dist;
        Ldist[seq[i - 1]][seq[k]] = Ldist[seq[k]][seq[i - 1]] = Dist;
    }

    //在下面用2-opt对路径进行调整
    for(register int i = 0; i < 1000000; i++) {
        int spoint = rand() % goalnum;
        int epoint = rand() % goalnum;
        if(spoint >= epoint) {
            i--;
            continue;
        }
        int *newseq = (int *)malloc(sizeof(int) * goalnum);
        //对原来序列进行翻转操作
        for(int i = 0; i < spoint; i++) {
            newseq[i] = seq[i];
        }
        for(int i = spoint; i <= epoint; i++) {
            newseq[i] = seq[spoint + epoint - i];
        }
        for(int i = epoint + 1; i < goalnum; i++) {
            newseq[i] = seq[i];
        }

        int Dist;
        int distsum = 0;
        memset(Vis, 0, sizeof(int) * goalnum);
        if(Lstart[newseq[0]] != -1) {
            distsum += Lstart[newseq[0]];
        } else {
            Path = bfs(state, state.start_x, state.start_y, goal[newseq[0]].x, goal[newseq[0]].y, &Dist, Lo, Vis);
            free(Path);
            distsum += Dist;
            Lstart[newseq[0]] = Dist;
        }
        for(int i = 1; i < goalnum; i++) {
            int k = i;
            while(k < goalnum) {
                if(Vis[seq[k]] == 1)//如果这个豆子已经被访问
                    k++;
                else
                    break;
            }
            if(k == goalnum)
                break;//说明豆子已经被吃光，跳出循环

            if(Ldist[newseq[i - 1]][newseq[k]] != -1)
                distsum += Ldist[newseq[i - 1]][newseq[k]];
            else {
                Path = bfs(state, goal[newseq[i - 1]].x, goal[newseq[i - 1]].y, goal[newseq[k]].x, goal[newseq[k]].y, &Dist, Lo, Vis);
                free(Path);
                distsum += Dist;
                Ldist[newseq[i - 1]][newseq[k]] = Ldist[newseq[k]][newseq[i - 1]] = Dist;
            }
        }
        if(distsum < mindist) {
            mindist = distsum;
            memcpy(seq, newseq, sizeof(int) * goalnum);
        }
        free(newseq);
    }


    //
    memset(Vis, 0, sizeof(int) * goalnum);
    Path = bfs(state, state.start_x, state.start_y, goal[seq[0]].x, goal[seq[0]].y, &Dist, Lo, Vis);
    printf("%s", Path);
    free(Path);

    for(int i = 1; i < goalnum; i++) {
        int k = i;
        while(k < goalnum) {
            if(Vis[seq[k]] == 1)//如果这个豆子已经被访问
                k++;
            else
                break;
        }
        if(k == goalnum)
            break;//说明豆子已经被吃光，跳出循环

        Path = bfs(state, goal[seq[i - 1]].x, goal[seq[i - 1]].y, goal[seq[k]].x, goal[seq[k]].y, &Dist, Lo, Vis);
        printf("%s", Path);
        free(Path);
    }
    free(goal);
    free(seq);
    for(int i = 0; i < state.n; i++) {
        free(Lo[i]);
    }
    free(Lo);
    for(int i = 0; i < goalnum; i++) {
        free(Ldist[i]);
    }
    free(Ldist);
    free(Lstart);
    free(Vis);
  // 
  destroy(&state);
  return 0;
}
