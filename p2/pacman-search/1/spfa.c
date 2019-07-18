#include "util.h"
#include <stdio.h>
#include <string.h>
#include "cqueue.h"
#include "cqueue.c"

int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here

    const double INF = 1073741824;

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
    int *inqueue = (int *)malloc(sizeof(int) * state.m * state.n);//用于记录点是否在队列中
    int *inqueueNum = (int *)malloc(sizeof(int) * state.m * state.n);//用于记录点入队的次数
    int *step = (int *)malloc(sizeof(int) * state.m * state.n);//用于记录步数
    double *dist = (double *)malloc(sizeof(double) * state.m * state.n);//用于记录最短距离
    for(int i = 0; i < state.m * state.n; i++) {
        inqueue[i] = 0;
        inqueueNum[i] = 0;
        step[i] = 0;
        dist[i] = INF;
    }
    CQueue *q = InitCQueue(state.m * state.n + 5);
    int data = state.start_x * state.m + state.start_y;
    CQueueType start;//将起点入队
    start.data = data;
    start.distance = 0;
    enCQueue(q, start);
    inqueue[data] = 1;
    inqueueNum[data]++;
    step[data] = -1;
    dist[data] = 0;
    while(!CQueueEmpty(q)) {
        CQueueType elem;
        deCQueue(q, &elem);
        inqueue[elem.data] = 0;
        int x = elem.data / state.m;
        int y = elem.data % state.m;
        for(int i = 0; i < 4; i++) {
            int data = (x + dirx[i]) * state.m + (y + diry[i]);
            if(x + dirx[i] >= 0 && x + dirx[i] < state.n
            && y + diry[i] >= 0 && y + diry[i] < state.m
            && state.grid[x + dirx[i]][y + diry[i]] == 0) {
                if(dist[data] > dist[elem.data] + state.cost[x + dirx[i]][y + diry[i]]) {//进行松弛操作
                    dist[data] = dist[elem.data] + state.cost[x + dirx[i]][y + diry[i]];
                    step[data] = step[elem.data] + 1;
                    path[x + dirx[i]][y + diry[i]] = dir[i];
                    if(inqueue[data] == 0) {
                        CQueueType in;
                        in.data = data;
                        in.distance = dist[data];
                        enCQueue(q, in);
                        inqueue[data] = 1;
                        inqueueNum[data]++;
                        if(inqueueNum[data] > state.n * state.m);//这个有负权环今后再加
                    }
                }
            }
        }
    }
    data = state.goal_x * state.m + state.goal_y;
    char *minpath = (char *)malloc(state.n * state.m);
    for(int i = 0; i < state.n * state.m; i++)
        minpath[i] = '\0';
    int i = state.goal_x, j = state.goal_y;
    int stepx = step[data];
    while(stepx >= 0) {
        minpath[stepx] = path[i][j];
        stepx--;
        switch(path[i][j]) {
        case 'W':j++;break;
        case 'E':j--;break;
        case 'N':i++;break;
        case 'S':i--;break;
        }
    }
    printf("%s", minpath);
    free(minpath);
    free(inqueue);
    free(inqueueNum);
    free(step);
    free(dist);
    DestroyCQueue(q);

    // 
    destroy(&state);
    return 0;
}
