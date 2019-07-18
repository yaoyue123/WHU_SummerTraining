#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

typedef struct {
    int data;
    double priority;
    int dir;
    int step;
    double dist;
} HeapType;

typedef struct {
    HeapType *data;
    int *list;//用来存储元素对应位置的地址表
    int n;
    int MaxSize;
} Heap;

Heap *InitHeap(int MaxSize);    //初始化堆
void DestroyHeap(Heap *h);      //销毁堆
void siftDown(Heap *h, int low, int high);  //向下筛选
void siftUp(Heap *h, int n);    //向上筛选
void InsertHeap(Heap *h, HeapType e);   //向堆中插入元素
void PopHeap(Heap *h, HeapType *e);  //从堆中取出元素

Heap *InitHeap(int MaxSize) 
{
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (HeapType *)malloc(sizeof(HeapType) * (MaxSize + 1));
    h->list = (int *)malloc(sizeof(int) * (MaxSize + 1));
    h->MaxSize = MaxSize;
    h->n = 0;
    return h;
}

void DestroyHeap(Heap *h)
{
    free(h->data);
    free(h->list);
    free(h);
}

void siftDown(Heap *h, int low, int high)
{
    int i = low, j = 2 * i;
    HeapType tmp = h->data[i];
    while(j <= high)
    {
        if(j < high && h->data[j].priority > h->data[j + 1].priority)//priority值越小优先级越高
            j++;
        if(tmp.priority > h->data[j].priority)
        {	h->data[i] = h->data[j];
            h->list[h->data[i].data] = i;//j向上移到i的位置，故更新地址表
            i = j;
         	j = 2 * i;
        }
        else break;
    }
    h->data[i] = tmp;
    h->list[tmp.data] = i;//tmp到了新的i位置，故更新地址表
}

void siftUp(Heap *h, int n)
{
    HeapType tmp = h->data[n];
    int i = n, j = n / 2;
    while(j >= 1)
    {
        if(h->data[j].priority > tmp.priority)
        {
            h->data[i] = h->data[j];
            h->list[h->data[i].data] = i;//j的元素向下移到了i位置，故更新地址表
            i = j;
            j /= 2;
        }
        else break;
    }
    h->data[i] = tmp;
    h->list[tmp.data] = i;//tmp存放的元素上移到了i位置，故更新地址表
}

void InsertHeap(Heap *h, HeapType e)
{
    if(h->n == h->MaxSize)
        return;
    h->n++;
    h->data[h->n] = e;
    h->list[e.data] = h->n;
    siftUp(h, h->n);
}

void PopHeap(Heap *h, HeapType *e)
{
    if(h->n == 0)
        return;
    (*e) = h->data[1];
    h->list[(*e).data] = 0;
    h->data[1] = h->data[h->n];
    h->n--;
    siftDown(h, 1, h->n);
}


int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here

    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    char **path = malloc(sizeof(char *) * state.n);
    for(int i = 0; i < state.n; i++) {//记录到这个点的方向
        path[i] = malloc(state.m);
        for(int j = 0; j < state.m; j++) {
            path[i][j] = 0;
        }
    }
    //规定：每个点的编号为i*m+j
    const double INF = 1073741824;
    Heap *h = InitHeap(state.m * state.n + 5);
    HeapType start;
    start.data = state.start_x * state.m + state.start_y;
    start.priority = 0;
    start.dir = 0;
    start.step = -1;
	InsertHeap(h, start);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if((i != state.start_x || j != state.start_y)
            && state.grid[i][j] == 0) {
                HeapType tmp;
                tmp.data = i * state.m + j;
                tmp.priority = INF;
                tmp.dir = 0;
                tmp.step = -1;
                InsertHeap(h, tmp);
            }
        }
    }
    while(h->n > 0) {
        HeapType elem;
        PopHeap(h, &elem);
        if(elem.data / state.m == state.goal_x && elem.data % state.m == state.goal_y) {//找到终点
            char *minpath = (char *)malloc(state.n * state.m);
            for(int i = 0; i < state.n * state.m; i++)
                minpath[i] = '\0';
            int i = elem.data / state.m, j = elem.data % state.m;
            int step = elem.step;
            while(step >= 0) {
                minpath[step] = path[i][j];
                step--;
                switch(path[i][j]) {
                case 'W':j++;break;
                case 'E':j--;break;
                case 'N':i++;break;
                case 'S':i--;break;
                }
            }
            printf("%s", minpath);
            free(minpath);
            break;
        }
        int x = elem.data / state.m;
        int y = elem.data % state.m;
        for(int i = 0; i < 4; i++) {
            int data = (x + dirx[i]) * state.m + (y + diry[i]);
            if(x + dirx[i] >= 0 && x + dirx[i] < state.n
            && y + diry[i] >= 0 && y + diry[i] < state.m
            && h->list[data] != 0 && state.grid[x + dirx[i]][y + diry[i]] == 0) {
                if(h->data[h->list[data]].priority > elem.priority + state.cost[x + dirx[i]][y + diry[i]]) {
                    h->data[h->list[data]].priority = elem.priority + state.cost[x + dirx[i]][y + diry[i]];
                    h->data[h->list[data]].step = elem.step + 1;
                    path[x + dirx[i]][y + diry[i]] = dir[i];
                    siftUp(h, h->list[data]);
                }
            }
        }
    }
    for(int i = 0; i < state.n; i++) {
        free(path[i]);
    }
    free(path);
    DestroyHeap(h);

    // 
    destroy(&state);
    return 0;
}
