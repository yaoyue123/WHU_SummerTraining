#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    int wallNum = 0;
    for(int i = 1; i < state.n - 1; i++) {
        for(int j = 1; j < state.m - 1; j++) {
            if(state.grid[i][j] == 1) {
                wallNum++;
            }
        }
    }


    if(state.index == 0 && wallNum > 10) {
    const double INIT = 0;
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    double cost[4] = {INIT,INIT,INIT,INIT};

    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                int dist;
                char *path = bfs(state, state.start_x, state.start_y, i, j, &dist);
                if(path != NULL) {
                    int x = state.start_x;
                    int y = state.start_y;
                    int m = 0;
                    while(x != i && y != j) {
                        for(int k = 0; k < 4; k++) {
                            int endx = state.ghost_x[state.index] + dirx[k];
                            int endy = state.ghost_y[state.index] + diry[k];
                            if(state.grid[endx][endy] != 1) {
                                int dist;
                                char *path = bfs(state, endx, endy, x, y, &dist);
                                free(path);
                                cost[k] += dist;
                            }
                        }
                        switch(path[m]) {
                        case 'E':
                            x += dirx[0];
                            y += diry[0];
                            break;
                        case 'S':
                            x += dirx[1];
                            y += diry[1];
                            break;
                        case 'W':
                            x += dirx[2];
                            y += diry[2];
                            break;
                        case 'N':
                            x += dirx[3];
                            y += diry[3];
                            break;
                        default:
                            goto out;
                        }
                        m++;
                    }
                out:free(path);
                }
            }
        }
    }

    int min = 1073741824;
    char ch = 'E';
    for(int i = 0; i < 4; i++) {
        int endx = state.ghost_x[state.index] + dirx[i];
        int endy = state.ghost_y[state.index] + diry[i];
        if(state.grid[endx][endy] == 1)
            continue;
        if(min > cost[i]) {
            min = cost[i];
            ch = dir[i];
        }
    }
    printf("%c", ch);
    } else {
    int dirx[4] = { 0, 1, 0,-1};
    int diry[4] = { 1, 0,-1, 0};
    char dir[4] = {'E','S','W','N'};
    int distance[4] = {-1,-1,-1,-1};

    for(int i = 0; i < 4; i++) {
        int endx = state.ghost_x[state.index] + dirx[i];
        int endy = state.ghost_y[state.index] + diry[i];
        if(state.grid[endx][endy] == 0) {
            if(endx == state.start_x && endy == state.start_y) {
                distance[i] = 0;
            } else {
                char *path = bfs(state, endx, endy, state.start_x, state.start_y, &distance[i]);
                if(path != NULL) {
                    free(path);
                }
            }
        }
    }

    const int INF = 1073741824;
    int min = INF;
    char ch;
    int x;
    for(int i = 0, x = state.index; i < 4; i++, x++) {
        if(distance[x % 4] != -1 && distance[x % 4] < min) {
            min = distance[x % 4];
            ch = dir[x % 4];
        }
    }
    if(min != INF) {
        printf("%c", ch);
    }
    }


  //
  destroy(&state);
  return 0;
}
