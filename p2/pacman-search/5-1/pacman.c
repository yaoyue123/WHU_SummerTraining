#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
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

    if(!state.is_red) {
        return 0;
    }

    int beanNum = 0, leftBeanNum = 0;
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                beanNum++;
                if(j < (double)state.m / 4) {
                    leftBeanNum++;
                }
            }
        }
    }

    int bflag = 0;
    if((double)beanNum / (leftBeanNum + 1) <= 2) {
        bflag = 1;
    }

    srand(time(NULL));
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    double cost[4] = {0, 0, 0, 0};

    //根据鬼的位置给四个方位赋权值
    for(int i = 0; i < state.num_ghosts; i++) {
        for(int j = 0; j < 4; j++) {
            int endx = state.red_x + dirx[j];
            int endy = state.red_y + diry[j];
            if(state.grid[endx][endy] != 1) {
                if(endx == state.ghost_x[i] && endy == state.ghost_y[i]) {
                    if(bflag == 0)
                        cost[j] += exp(28);
                    else
                        cost[j] -= exp(2);
                } else {
                    int dist;
                    char *path = bfs(state, endx, endy, state.ghost_x[i], state.ghost_y[i], &dist);
                    free(path);
                    if(bflag == 0)
                        cost[j] += exp(28 - dist * 15);
                    else
                        cost[j] -= exp(2 - dist * 1.2);
                }
            }
        }
    }
    //根据食物的位置给四个方位赋权值
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            for(int k = 0; k < 4; k++) {
                if(state.food[i][j] == 1) {
                    int dist;
                    char *path = bfs(state, state.blue_x, state.blue_y, i, j, &dist);
                    free(path);
                    if(dist <= 3 && abs(state.red_x - i) + abs(state.red_y - j) > dist)
                        break;

                    int endx = state.red_x + dirx[k];
                    int endy = state.red_y + diry[k];
                    if(state.grid[endx][endy] == 1) {
                        cost[k] = 907374782400;
                    } else if(endx == i && endy == j) {
                        cost[k] -= exp(8);
                    }
                    else {
                        int dist;
                        char *path = bfs(state, i, j, endx, endy, &dist);
                        if(path != NULL) {
                            if(dist <= 3)
                                cost[k] -= exp(8 - (double)dist * 0.9);
                            else
                                cost[k] -= exp(4 - (double)dist / 7);
                            free(path);
                        }
                    }  
                }
            }
        }
    }

    double min = 907374182400;
    char ch = 'A';
    int index;
    for(int i = 0, index = rand() % 200; i < 4; i++, index++) {
        int endx = state.red_x + dirx[index % 4];
        int endy = state.red_y + diry[index % 4];
        if(state.grid[endx][endy] == 1)
            continue;
        if(min > cost[index % 4]) {
            min = cost[index % 4];
            ch = dir[index % 4];
        }
    }

    if(ch != 'A') {
        printf("%c", ch);
    }



    //
  destroy(&state);
  return 0;
}