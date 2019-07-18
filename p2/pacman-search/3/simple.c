#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    double cost[4] = {0, 0, 0, 0};
    const double INF = 1073741824;
    for(int i = 0; i < state.num_ghosts; i++) {//通过鬼的位置调整权值
        for(int j = 0; j < 4; j++) {
            int endx = state.start_x + dirx[j];
            int endy = state.start_y + diry[j];
            if(state.grid[endx][endy] == 1) {
                cost[j] = INF;
            } else if(endx == state.ghost_x[i] && endy == state.ghost_y[i]) {
                cost[j] += exp(23);
            } else {
                int dist;
                char *path = bfs(state, state.ghost_x[i], state.ghost_y[i], endx, endy, &dist);
                if(path != NULL) {
                    cost[j] += exp(23 - dist * 4);
                    free(path);
                }
            }
        }
    }

    for(int i = 0; i < state.n; i++) {//通过食物的位置调整权值
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                for(int k = 0; k < 4; k++) {
                    int endx = state.start_x + dirx[k];
                    int endy = state.start_y + diry[k];
                    if(state.grid[endx][endy] == 1) {
                        cost[k] = INF;
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

    double min = INF - 100;
    char ch = 'A';

    for(int i = 0; i < 4; i++) {
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
