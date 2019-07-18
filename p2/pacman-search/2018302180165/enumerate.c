#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "queue.h"

typedef struct {
    int x;
    int y;
} Point;

char *bfs(game_state_t state, int start_x, int start_y, int goal_x, int goal_y, int *dis) {
    int dirx[4] = {0, 1, 0, -1};
    int diry[4] = {1, 0, -1, 0};
    char dir[4] = {'E','S','W','N'};
    int **visit = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        visit[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++)
            visit[i][j] = 0;
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
            if(elem.x >= 0 && elem.x < state.n&& elem.y >= 0 && elem.y < state.m&& visit[elem.x][elem.y] == 0 && state.grid[elem.x][elem.y] == 0) {
                visit[elem.x][elem.y] = 1;
                enQueue(q, elem);
                if(elem.x == goal_x && elem.y == goal_y) {
                    int i = q->rear;
                    (*dis) = q->data[i].step + 1;
                    while(q->data[i].step >= 0) {
                        path[q->data[i].step] = q->data[i].dir;
                        i = q->data[i].before;
                    }
                    for(int i = 0; i < state.n; i++)
                    	free(visit[i]);
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

void Enumerate(game_state_t state, Point *bean, int beanNum, int *seq, int t, int **disList, int *startList, \
        int *bestseq, int *mindis, int *visit) 
{
    if(t == beanNum) {
        int dissum = 0;
        if(startList[seq[0]] != -1) {
            dissum += startList[seq[0]];
        }
        else {
            int dis;
            char *path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dis);
            free(path);
            dissum += dis;
            startList[seq[0]] = dis;
        }

        for(int i = 1; i < beanNum; i++) {
            if(disList[seq[i - 1]][seq[i]] != -1) {
                dissum += disList[seq[i - 1]][seq[i]];
            }
            else {
                int dis;
                char *path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[i]].x, bean[seq[i]].y, &dis);
                free(path);
                dissum += dis;
                disList[seq[i - 1]][seq[i]] = disList[seq[i]][seq[i - 1]] = dis;
            }
        }

        if(dissum < (*mindis)) {
            (*mindis) = dissum;
            memcpy(bestseq, seq, sizeof(int) * beanNum);
        }
        return;
    }
    for(int i = 0; i < beanNum; i++) {
        if(visit[i] == 0) {
            seq[t] = i;visit[i] = 1;
            Enumerate(state, bean, beanNum, seq, t + 1, disList, startList, bestseq, mindis, visit);
            visit[i] = 0;
        }
    }
}
int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
    srand(time(NULL));
    Point *bean;
    int beanNum = 0;
    int **location = malloc(sizeof(int *) * state.n);
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    bean = (Point *)malloc(sizeof(Point) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {
                bean[beanNum].x = i;
                bean[beanNum].y = j;
                location[i][j] = beanNum;beanNum++;
            }
        }
    }
    int *startList = malloc(sizeof(int) * beanNum);
    int **disList = malloc(sizeof(int *) * beanNum);
    for(int i = 0; i < beanNum; i++) {
        startList[i] = -1;
        disList[i] = malloc(sizeof(int) * beanNum);
        for(int j = 0; j < beanNum; j++)
            disList[i][j] = -1;
    }
    int *seq = (int *)malloc(sizeof(int) * (beanNum + 5));
    int *bestseq = (int *)malloc(sizeof(int) * (beanNum + 5));
    int *visit = (int *)malloc(sizeof(int) * beanNum);
    for(int i = 0; i < beanNum; i++)
        visit[i] = 0;
    int mindis = 1073741824;
    Enumerate(state, bean, beanNum, seq, 0, disList, startList, bestseq, &mindis, visit);
    //
    int dis;
    char *path = bfs(state, state.start_x, state.start_y, bean[bestseq[0]].x, bean[bestseq[0]].y, &dis);
    printf("%s", path);
    free(path);
    for(int i = 1; i < beanNum; i++) {
        path = bfs(state, bean[bestseq[i - 1]].x, bean[bestseq[i - 1]].y, bean[bestseq[i]].x, bean[bestseq[i]].y, &dis);
        printf("%s", path);
        free(path);
    }
    for(int i = 0; i < state.n; i++)
        free(location[i]);
    free(location);
    for(int i = 0; i < beanNum; i++)
        free(disList[i]);
    free(bean);
    free(seq);
    free(bestseq);
    free(visit);
    free(disList);
    free(startList);
 //
  destroy(&state);
  return 0;
}
