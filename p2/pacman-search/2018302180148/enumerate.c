#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

typedef struct {
    int x;
    int y;
} Point;


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

void enumerate(game_state_t state, Point *bean, int beanNum, int *seq, int t, int **distList, int *startList, \
        int *bestseq, int *mindist, int *visit) 
{
    if(t == beanNum) {
        int distsum = 0;
        if(startList[seq[0]] != -1) {
            distsum += startList[seq[0]];
        }
        else {
            int dist;
            char *path = bfs(state, state.start_x, state.start_y, bean[seq[0]].x, bean[seq[0]].y, &dist);
            free(path);
            distsum += dist;
            startList[seq[0]] = dist;
        }

        for(int i = 1; i < beanNum; i++) {
            if(distList[seq[i - 1]][seq[i]] != -1) {
                distsum += distList[seq[i - 1]][seq[i]];
            }
            else {
                int dist;
                char *path = bfs(state, bean[seq[i - 1]].x, bean[seq[i - 1]].y, bean[seq[i]].x, bean[seq[i]].y, &dist);
                free(path);
                distsum += dist;
                distList[seq[i - 1]][seq[i]] = distList[seq[i]][seq[i - 1]] = dist;
            }
        }

        if(distsum < (*mindist)) {
            (*mindist) = distsum;
            memcpy(bestseq, seq, sizeof(int) * beanNum);
        }
        return;
    }
    for(int i = 0; i < beanNum; i++) {
        if(visit[i] == 0) {
            seq[t] = i;
            visit[i] = 1;
            enumerate(state, bean, beanNum, seq, t + 1, distList, startList, bestseq, mindist, visit);
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
    Point *bean;//用来记录豆子位置的数组
    int beanNum = 0;//用来记录豆子个数的数组
    int **location = malloc(sizeof(int *) * state.n);//用于记录食物在数组中的位置
    for(int i = 0; i < state.n; i++) {
        location[i] = malloc(sizeof(int) * state.m);
        for(int j = 0; j < state.m; j++) {
            location[i][j] = -1;
        }
    }
    bean = (Point *)malloc(sizeof(Point) * state.n * state.m);
    for(int i = 0; i < state.n; i++) {
        for(int j = 0; j < state.m; j++) {
            if(state.food[i][j] == 1) {//如果这个地方有食物，就把这个食物位置加入数组
                bean[beanNum].x = i;
                bean[beanNum].y = j;
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

    int *seq = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录吃豆子的顺序
    int *bestseq = (int *)malloc(sizeof(int) * (beanNum + 5));//用于记录最佳吃豆子顺序
    int *visit = (int *)malloc(sizeof(int) * beanNum);//枚举函数有用
    for(int i = 0; i < beanNum; i++) {
        visit[i] = 0;
    }
    int mindist = 1073741824;

    enumerate(state, bean, beanNum, seq, 0, distList, startList, bestseq, &mindist, visit);
    //
    int dist;
    char *path = bfs(state, state.start_x, state.start_y, bean[bestseq[0]].x, bean[bestseq[0]].y, &dist);
    printf("%s", path);
    free(path);

    for(int i = 1; i < beanNum; i++) {
        path = bfs(state, bean[bestseq[i - 1]].x, bean[bestseq[i - 1]].y, bean[bestseq[i]].x, bean[bestseq[i]].y, &dist);
        printf("%s", path);
        free(path);
    }

    free(bean);
    free(seq);
    free(bestseq);
    free(visit);
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
