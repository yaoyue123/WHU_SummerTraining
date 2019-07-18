#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "queue.h"

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

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    srand(time(NULL));
    
    int wallNum = 0;
    for(int i = 1; i < state.n - 1; i++) {
        for(int j = 1; j < state.m - 1; j++) {
            if(state.grid[i][j] == 1) {
                wallNum++;
            }
        }
    }


    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    double cost[4] = {0, 0, 0, 0};

    //根据鬼的状态和位置赋初值
    int flag = 0;//用来标记是否有鬼变白
    int eflag = 0;//用来标记是否有鬼保持原样
    for(int i = 0; i < 4; i++) {
        int endx = state.start_x + dirx[i];
        int endy = state.start_y + diry[i];
        for(int j = 0; j < state.num_ghosts; j++) {
            if(state.timer[j] <= 6) {//如果这个鬼即将复原或已经复原
                eflag = 1;
                if(state.grid[endx][endy] == 0) {//如果周围的这个点不是墙
                    if(endx == state.ghost_x[j] && endy == state.ghost_y[j]) {
                        cost[i] += exp(23);
                    } else {
                        int dist;
                        char *path = bfs(state, endx, endy, state.ghost_x[j], state.ghost_y[j], &dist);
                        free(path);
                        if(wallNum < 10)
                            cost[i] += exp(23 - dist * 4);
                        else
                            cost[i] += exp(23 - (double)dist * 3.5);
                    }
                }
            } else {//如果这个鬼还要很久复原
                flag = 1;
                if(state.grid[endx][endy] == 0) {//如果周围的这个点不是墙
                    if(endx == state.ghost_x[j] && endy == state.ghost_y[j]) {
                        if(wallNum > 10)
                            cost[i] += exp(8);
                        else
                            cost[i] += exp(15);
                    } else {
                        int dist;
                        char *path = bfs(state, endx, endy, state.ghost_x[j], state.ghost_y[j], &dist);
                        free(path);
                        if(wallNum > 10)
                            cost[i] += exp(8 - (double)dist / 2);
                        else
                            cost[i] += exp(15 - dist * 4);
                    }
                }
            }
        }
    }

    //如果有鬼没复原，且鬼离鬼窝的距离较近，就尽量远离鬼窝
    if(flag == 1) {
        for(int i = 0; i < 4; i++) {
            int endx = state.start_x + dirx[i];
            int endy = state.start_y + diry[i];
            int middlex = (state.n - 1) / 2;
            int middley = (state.m - 1) / 2;
            while(state.grid[middlex][middley] == 1) {
                if(rand() % 2)
                    middlex++;
                else
                    middlex--;
            }
            int mindist = 1000000;//离鬼窝最近的点到鬼窝的距离
            for(int i = 0; i < state.num_ghosts; i++) {
                int dist;
                char *path = bfs(state, middlex, middley, state.ghost_x[i], state.ghost_y[i], &dist);
                free(path);
                if(dist < mindist)
                    mindist = dist;
            }
            if(mindist > 3)
                break;
            if(state.grid[endx][endy] == 0) {
                if(endx == middlex && endy == middley) {
                    cost[i] += exp(25);
                } else {
                    int dist;
                    char *path = bfs(state, endx, endy, middlex, middley, &dist);
                    free(path);
                    cost[i] += exp(25 - dist * 4);
                }
            }
        }
    }

    //通过食物位置给cost赋值
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                for(int k = 0; k < 4; k++) {
                    int endx = state.start_x + dirx[k];
                    int endy = state.start_y + diry[k];
                    if(state.grid[endx][endy] == 1) {
                        cost[k] = 907374782400;
                    } else if(endx == i && endy == j) {
                        cost[k] -= exp(14);
                    }
                    else {
                        int dist;
                        char *path = bfs(state, i, j, endx, endy, &dist);
                        if(path != NULL) {
                            cost[k] -= exp(14 - (double)dist / 2);
                            free(path);
                        }
                    }
                }
            }
        }
    }

    //通过胶囊位置给cost赋值
    for(int i = 0; i < 4; i++) {
        int endx = state.start_x + dirx[i];
        int endy = state.start_y + diry[i];
        for(int j = 0; j < state.num_capsule; j++) {
            if(state.grid[endx][endy] == 0) {
                if(endx == state.capsule_x[j] && endy == state.capsule_y[j]) {
                    if(flag == 0)
                        cost[i] -= exp(15);
                    else if(eflag == 1)
                        cost[i] -= exp(12);
                    else
                        cost[i] -= exp(8);
                } else {
                    int dist;
                    char *path = bfs(state, endx, endy, state.capsule_x[j], state.capsule_y[j], &dist);
                    if(path != NULL) {
                        if(flag == 0)
                            cost[i] -= exp(15 - (double)dist / 2);
                        else if(eflag == 1)
                            cost[i] -= exp(12 - (double)dist / 2);
                        else
                            cost[i] -= exp(8 - (double)dist / 2);
                        free(path);
                    }
                }
            }
        }
    }

    double min = 907374782400;
    char ch = 'A';

    for(int i = 0; i < 4; i++) {
        int endx = state.start_x + dirx[i];
        int endy = state.start_y + diry[i];
        if(state.grid[endx][endy] == 1)
            continue;
        int middlex = (state.n - 1) / 2;
        int middley = (state.m - 1) / 2;
        if(endx == middlex && (abs(endy - middley) == 1))
            continue;
        if(min > cost[i]) {
            min = cost[i];
            ch = dir[i];
        }
    }
    if(ch != 'A') {
        printf("%c", ch);
    }
  //
  destroy(&state);
  return 0;
}
