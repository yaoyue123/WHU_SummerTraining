#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

typedef struct {
    int x;
    int y;
}Point;

char *shortestPath(game_state_t state, Point *point, int pointNum) {
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
    char *pathsum = (char *)malloc(sizeof(char) * state.n * state.m * 40);
    for(int i = 0; i < state.n * state.m; i++) {
        pathsum[i] = 0;
        path[i] = 0;
    }
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
                if(elem.x == point[ppoint].x && elem.y == point[ppoint].y) {
                    int i = q->rear;
                    while(q->data[i].step >= 0) {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    strcat(pathsum, path);
                    for(int i = 0; i < state.n * state.m; i++)
                        path[i] = 0;
                    DestroyQueue(q);
                    q = InitQueue(state.m * state.n);
                    elem.step = -1;
                    elem.before = -1;
                    state.food[elem.x][elem.y] = 0;
                    enQueue(q, elem);
                    ppoint++;
                    if(ppoint == pointNum) {
                        goto end;
                    }
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
end:
    free(path);
    for(int i = 0; i < state.n; i++) {
        free(visit[i]);
    }
    free(visit);
    DestroyQueue(q);
    return pathsum;
}

char *shortestPathsum(game_state_t state, Point *point, int pointNum, int seq[]) {
    Point *newp = (Point *)malloc(sizeof(Point) * (pointNum + 5)); 
    for(int i = 0; i < pointNum; i++) {
        newp[i] = point[seq[i]];
    }
    char *pathsum = shortestPath(state, newp, pointNum);
    free(newp);
    return pathsum;
}

void enumerate(game_state_t state, Point *point, int pointNum, int seq[], int i, int visit[], char *minpath) {
    char *path;
    if(i == pointNum) {
        path = shortestPathsum(state, point, pointNum, seq);
        if(strlen(path) < strlen(minpath)) {
            strcpy(minpath, path);
        }
        free(path);
        return;
    }
    for(int j = 0; j < pointNum; j++) {
        if(visit[j] == 0) {
            seq[i] = j;
            visit[j] = 1;
            enumerate(state, point, pointNum, seq, i + 1, visit, minpath);
            visit[j] = 0;
        }
    }
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    Point *point = (Point *)malloc(sizeof(Point) * state.m * state.n);
    int pointnum = 0;
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                Point p;
                p.x = i;
                p.y = j;
                point[pointnum] = p;
                pointnum++;
            }
        }
    }
    char *minpath = (char *)malloc(state.m * state.n);
    int *visit = (int *)malloc(sizeof(int) * state.m * state.n);
    int *seq = (int *)malloc(sizeof(int) * 40);
    for(int i = 0; i < state.m * state.n; i++) {
        minpath[i] = 'E';
        visit[i] = 0;
    }
    minpath[state.m * state.n - 1] = '\0';
    enumerate(state, point, pointnum, seq, 0, visit, minpath);
    printf("%s", minpath);
    free(minpath);
    free(visit);
    free(seq);
    free(point);

  // 
  destroy(&state);
  return 0;
}
